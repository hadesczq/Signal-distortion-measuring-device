#include "Header_Config.h"
#include<math.h>
#include "Fourier.h"
#include "uart.h"
#include<stdio.h>
#include<stdlib.h>
#include "oled.h"
#include "type.h"


int flag = 0, max_i = 1;
float flag1 = 0, max = 0, fn = 0, Ac = 0, Dc = 0, ph = 0, fs = 5462, flag2 = 10000/(256);                  //fs
struct compx data[FFT_N]={0};                                  //128
char display[8];
char DisplayNA_1[8];
char DisplayNA_2[8];
char DisplayNA_3[8];
char DisplayNA_4[8];
char strthd[16];
char strna1[16];
char strna2[16];
char strna3[16];
char strna4[16];
float adv[FFT_N];
float Mag;//datamag数组变量中间值
float datamag[FFT_N]; 
float p,l,m,THD;//p为直流分量，基波幅值，l为THD计算公式分子部分（未开方），m为分子部分，THD
float num_ADC(float num);
float NA_1,NA_2,NA_3,NA_4;
void FFT_change(void);
void Powermag(void);
void debugtemp(void);
void SendData(struct compx *struct_buf, int size);
void SendFloat(struct compx *struct_buf, int sizeOfFloat);
void key_init(void);
void delay(int ms)        //延时函数
{
	for(int i=0;i<ms;i++)
	for(int j=0;j<240;j++);
}
void TA_Init(void)
{
  P5SEL |= BIT2|BIT3; //将IO配置为XT2功能
  UCSCTL6 &= ~(XT2OFF); //使能XT2
  
  //UCSCTL4 = UCSCTL4&(~(SELA_7))|SELA_1; //先将ACLK配置为 VLOCLK  
 // UCSCTL3 |= SELREF_2;                  //将REFCLK配置为 REFCLK  
 
  while (SFRIFG1 & OFIFG){
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);         // 清除三类时钟标志位
                              // 这里需要清除三种标志位，因为任何一种
                              // 标志位都会将OFIFG置位
    SFRIFG1 &= ~OFIFG;                                  // 清除时钟错误标志位
  }
  UCSCTL4 = UCSCTL4&(~(SELS_7|SELM_7))|SELS_5|SELM_5;     //将SMCLK和MCLK时钟源配置为XT2
  
  TA0CTL=TACLR+MC_1+TASSEL_2;
  //计数器TA2清零  /定时器2增模式; //选择ACLK时钟32.768KHZ，初级1分频,关闭TA2IFG中断
  TA0CCR0=400; //比较模式对比数值
  //TA0CCTL0=CCIE; //CCRO比较中断使能
  //TA0EX0=TAIDEX_0;//二级1分频
}
int main( void )
{
    int i;
  //  float wc;
    // Stop WDT
    
    WDTCTL = WDTPW + WDTHOLD;
  
    P1DIR=0Xff;
    P1OUT |= BIT7;
    P1REN |= BIT7;    //配置上拉电阻//0x3f   
    
    P2DIR=0Xff;
    P2OUT |= BIT2;
    P2REN |= BIT2;    //配置上拉电阻//0x3f 
    // Basic GPIO initialization
    Board_init();//滑轮什么的配置
    
    // Set Vcore to accomodate for max. allowed system speed
    //设置核心电压，以适应最大。让系统速度
    SetVCore(3);

    // Use 32.768kHz XTAL as reference
    //使用32.768kHz的XTAL作为参考
    LFXT_Start(XT1DRIVE_0);

    // Set system clock to max (25MHz)
    Init_FLL_Settle(25000, 762);

//    SFRIFG1 = 0;
//    SFRIE1 |= OFIE;//振荡器故障启用

    // Globally enable interrupts
    __enable_interrupt();
    // RTC
    SetupRTC();
    // Main loop
    ADC_init();
    TA_Init();
    UART0_INIT();
    OLED_Init();
    OLED_Clear();
    key_init();
    
    while (1)
    {       
     flag = 0;
      flag1 = 0;
      ADC12IE = 0x20;
      TA0CCTL0=CCIE;  
      while(flag<FFT_N)
      {
        ; //等待中断数据装满   
      }     
      // SendData(data, 256);
      TA0CCTL0&=!CCIE;
      ADC12IE = 0x00;
      
      for (i = 0; i < FFT_N; i++)
      {
        data[i].real = num_ADC(data[i].real); 
        data[i].imag = 0;
        
      } 
//      ///////////////////////////////////
//       for(i=8;i<FFT_N+8;i++)                        //给结构体赋值   
//	{       	
//                wc = 50*PI*2*(float)i/fs;
//		data[i-8].real=3*sin(wc+(PI/3));
//		data[i-8].imag=0;                             //虚部为0  
//	}         
//   
       // FFT(data);
       FFT_change();
        
       
//      
//      ////////////////////////////////////
      fn = ((float)(max_i)/FFT_N)*fs;
      Ac = (2*max)/FFT_N;
      Dc = data[0].real/FFT_N;
      Powermag();
    
//       while(1);
//     __bis_SR_register(LPM0_bits + GIE);     // Enter LPM4, Enable interrupts
//      __no_operation(); 
    }
}


void SendData(struct compx *struct_buf, int size)
{
  int i = 0, j = 0;
  char buf[8]={0};
  for(; i<size; i++)
  {
    sprintf(buf, "%.3f\r\n", struct_buf[i].real);
    for(j=0;buf[j] != 0; j++)
    {
       UART0_Sendchar(buf[j]);
    }
  }
}

void SendFloat(struct compx *struct_buf, int sizeOfFloat)
{
  int i = 0, j = 0;
  char *pS;
  for(j = 0; j < sizeOfFloat; j++)
  {
    pS = (char*)&struct_buf[j];
    for(i = 0;i < 4; i++)
    {
      UART0_Sendchar(pS[j]);
    }
    //这里最好延时一点
    delay(1);
  }
}

void SendString(char *string)
{
  int j=0;
    for(j=0; string[j] != 0; j++)
    {
       UART0_Sendchar(string[j]);
    }
}

#pragma vector=TIMER0_A0_VECTOR //CCR0中断标志
__interrupt void TA_CCO(void)
{
  flag1++;
  if(flag1==flag2)
  {
    flag1 = 0;
    data[flag].real = (float)ADC_Result1;
    flag++;
  }
}

float num_ADC(float num)
{
  float temp;
  
  temp = num;
  temp *= 330;
  temp /= 40960;
  temp /= 10;
  return temp;
}

void FFT_change(void)
{
  int i;
  float rea;
  
  FFT(data);
  //SendData(data, 256);
  max = sqrt(data[1].real*data[1].real+data[1].imag*data[1].imag);
  max_i = 1;
  if((data[1].real>0.001)||(data[1].real<-0.001)) ph = 57.3*atan(data[1].imag/data[1].real);
  else ph = 0;
  /****************/
  for(i=0;i<FFT_N;i++)                           //求变换后结果的模值，存入复数的实部部分 
  {
    rea = data[i].real;
    data[i].real=sqrt(data[i].real*data[i].real+data[i].imag*data[i].imag);   
    if(((data[i].real-max)>0.001)&&(i!=0))
    {
      max = data[i].real;
      max_i = i;
      if((rea>0.001)||(rea<-0.001)) ph = 57.3*atan(data[i].imag/rea);
      else ph = 0;
    }
  }
  //  SendData(data, 256);
} 
/*
*************************************************************
*   计算各次谐波幅值
*************************************************************
*/
void Powermag(void)
{
    int i;
    for(i=0;i<FFT_N/2;i++)
    {
        Mag=data[i].real/FFT_N;
        if(i==0)
          datamag[i]=Mag;
            //datamag[i] = Mag*FFT_N;
        else
          datamag[i]=Mag/2;
           // datamag[i] = (Mag*2)/FFT_N;
    }
    p=datamag[23];
    l=datamag[46]*datamag[46]+datamag[69]*datamag[69]+datamag[92]*datamag[92]+datamag[115]*datamag[115];
    //此处谐波幅值出现的位置待确认
    m=sqrt(l);
    THD=m/p;
    THD*=100;
    sprintf(strthd, "THD=%.2f%%", THD);
    SendString(strthd);
    //Normalized amplitude
    NA_1=datamag[46]/datamag[23];
    NA_2=datamag[69]/datamag[23];
    NA_3=datamag[92]/datamag[23];
    NA_4=datamag[115]/datamag[23];
    
    //开始显示
    OLED_Clear();
    OLED_ShowString(0,0,"THD=",8);
    sprintf(display, "%.2f%%", THD);
    OLED_ShowString(35,0,(unsigned char*)display,8);
    sprintf(DisplayNA_1, "%.2f", NA_1);
    sprintf(DisplayNA_2, "%.2f", NA_2);
    sprintf(DisplayNA_3, "%.2f", NA_3);
    sprintf(DisplayNA_4, "%.2f", NA_4);
    OLED_ShowString(7,3,"NA_1:",8);
    OLED_ShowString(7,4,"NA_2:",8);
    OLED_ShowString(7,5,"NA_3:",8);
    OLED_ShowString(7,6,"NA_4:",8);
    OLED_ShowString(45,3,(unsigned char*)DisplayNA_1,8);
    OLED_ShowString(45,4,(unsigned char*)DisplayNA_2,8);
    OLED_ShowString(45,5,(unsigned char*)DisplayNA_3,8);
    OLED_ShowString(45,6,(unsigned char*)DisplayNA_4,8);
    sprintf(strna1, "NA_1=%.2f\r\n", NA_1);
    sprintf(strna2, "NA_2=%.2f\r\n", NA_1);
    sprintf(strna3, "NA_3=%.2f\r\n", NA_1);
    sprintf(strna4, "NA_4=%.2f\r\n", NA_1) ; 
    SendString(strna1);
    SendString(strna2);
    SendString(strna3);
    SendString(strna4);
    while((P1IN&BIT1));
}
void key_init(void)
{
  P1DIR &=~BIT1;//板载按键s2设为输入
  P1REN =BIT1;//上拉电阻，提高稳定性
  P1OUT |=BIT1;//设置初始值为高电平
}
/*****************************************************
//把SMCL配置为XT2 4MHZ
 P5SEL=BIT2+BIT3;   //声明特殊功能，将用作外部时钟晶振XT2输入
 UCSCTL6&=~XT2OFF;  //开启XT2


系统稳定后，DCOCLK默认为2.097152MHZ，FLL默认2分频，则MCLK和SMCLK的频率都为1.048576MHZ

  if(flag!=flag2)
      {
        num = num_ADC(ADC_Result);    
        sprintf(zifu, "%.3f", num);    
        Dogs102x6_stringDraw(0, 0, zifu, DOGS102x6_DRAW_NORMAL);
        
        num1 = num_ADC(ADC_Result1);
        sprintf(zifu, "%.3f", num1);    
        Dogs102x6_stringDraw(1, 0, zifu, DOGS102x6_DRAW_NORMAL);
        
        flag2 = flag;
        
      }
      sprintf(zifu, "%d", flag);    
      Dogs102x6_stringDraw(2, 0, zifu, DOGS102x6_DRAW_NORMAL);
      
******************************************************/


