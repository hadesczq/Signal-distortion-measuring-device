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
float Mag;//datamag��������м�ֵ
float datamag[FFT_N]; 
float p,l,m,THD;//pΪֱ��������������ֵ��lΪTHD���㹫ʽ���Ӳ��֣�δ��������mΪ���Ӳ��֣�THD
float num_ADC(float num);
float NA_1,NA_2,NA_3,NA_4;
void FFT_change(void);
void Powermag(void);
void debugtemp(void);
void SendData(struct compx *struct_buf, int size);
void SendFloat(struct compx *struct_buf, int sizeOfFloat);
void key_init(void);
void delay(int ms)        //��ʱ����
{
	for(int i=0;i<ms;i++)
	for(int j=0;j<240;j++);
}
void TA_Init(void)
{
  P5SEL |= BIT2|BIT3; //��IO����ΪXT2����
  UCSCTL6 &= ~(XT2OFF); //ʹ��XT2
  
  //UCSCTL4 = UCSCTL4&(~(SELA_7))|SELA_1; //�Ƚ�ACLK����Ϊ VLOCLK  
 // UCSCTL3 |= SELREF_2;                  //��REFCLK����Ϊ REFCLK  
 
  while (SFRIFG1 & OFIFG){
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);         // �������ʱ�ӱ�־λ
                              // ������Ҫ������ֱ�־λ����Ϊ�κ�һ��
                              // ��־λ���ὫOFIFG��λ
    SFRIFG1 &= ~OFIFG;                                  // ���ʱ�Ӵ����־λ
  }
  UCSCTL4 = UCSCTL4&(~(SELS_7|SELM_7))|SELS_5|SELM_5;     //��SMCLK��MCLKʱ��Դ����ΪXT2
  
  TA0CTL=TACLR+MC_1+TASSEL_2;
  //������TA2����  /��ʱ��2��ģʽ; //ѡ��ACLKʱ��32.768KHZ������1��Ƶ,�ر�TA2IFG�ж�
  TA0CCR0=400; //�Ƚ�ģʽ�Ա���ֵ
  //TA0CCTL0=CCIE; //CCRO�Ƚ��ж�ʹ��
  //TA0EX0=TAIDEX_0;//����1��Ƶ
}
int main( void )
{
    int i;
  //  float wc;
    // Stop WDT
    
    WDTCTL = WDTPW + WDTHOLD;
  
    P1DIR=0Xff;
    P1OUT |= BIT7;
    P1REN |= BIT7;    //������������//0x3f   
    
    P2DIR=0Xff;
    P2OUT |= BIT2;
    P2REN |= BIT2;    //������������//0x3f 
    // Basic GPIO initialization
    Board_init();//����ʲô������
    
    // Set Vcore to accomodate for max. allowed system speed
    //���ú��ĵ�ѹ������Ӧ�����ϵͳ�ٶ�
    SetVCore(3);

    // Use 32.768kHz XTAL as reference
    //ʹ��32.768kHz��XTAL��Ϊ�ο�
    LFXT_Start(XT1DRIVE_0);

    // Set system clock to max (25MHz)
    Init_FLL_Settle(25000, 762);

//    SFRIFG1 = 0;
//    SFRIE1 |= OFIE;//������������

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
        ; //�ȴ��ж�����װ��   
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
//       for(i=8;i<FFT_N+8;i++)                        //���ṹ�帳ֵ   
//	{       	
//                wc = 50*PI*2*(float)i/fs;
//		data[i-8].real=3*sin(wc+(PI/3));
//		data[i-8].imag=0;                             //�鲿Ϊ0  
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
    //���������ʱһ��
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

#pragma vector=TIMER0_A0_VECTOR //CCR0�жϱ�־
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
  for(i=0;i<FFT_N;i++)                           //��任������ģֵ�����븴����ʵ������ 
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
*   �������г����ֵ
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
    //�˴�г����ֵ���ֵ�λ�ô�ȷ��
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
    
    //��ʼ��ʾ
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
  P1DIR &=~BIT1;//���ذ���s2��Ϊ����
  P1REN =BIT1;//�������裬����ȶ���
  P1OUT |=BIT1;//���ó�ʼֵΪ�ߵ�ƽ
}
/*****************************************************
//��SMCL����ΪXT2 4MHZ
 P5SEL=BIT2+BIT3;   //�������⹦�ܣ��������ⲿʱ�Ӿ���XT2����
 UCSCTL6&=~XT2OFF;  //����XT2


ϵͳ�ȶ���DCOCLKĬ��Ϊ2.097152MHZ��FLLĬ��2��Ƶ����MCLK��SMCLK��Ƶ�ʶ�Ϊ1.048576MHZ

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


