#include "Header_Config.h"

uint16_t ADC_Result, ADC_Result1, ceshi=0, ceshi1=0;

//ADC采样口为P6.4  6.5用做测试
void ADC_init(void)
{
    P8DIR |= BIT0;
    P8OUT |= BIT0;
    P6SEL |= BIT5+BIT4;                      // P6.5 ADC option select (A5)
    
    ADC12CTL0 = ADC12SHT0_4 + ADC12ON + ADC12MSC;                  // Sampling time, ADC12 on 
    /* ADC12采样保持0选择位：2   (ADC12MSC)ADC12多SampleConversion*/
    
    ADC12CTL1 = ADC12SHP+ADC12CONSEQ_3;           //5M  / /使用采样定时器      // Use sampling timer ADC12的最高采样频率为165KHz
    /*ADC12采样/保持脉冲模式    (ADC12CONSEQ_1)ADC12转换顺序选择：1*/
    
    ADC12MCTL4 = ADC12INCH_4;   
     /*(ADC12EOS)序列ADC12结束*/
    ADC12MCTL5 = ADC12INCH_5+ADC12EOS;                          // Use A5 (wheel) as input
    
    ADC12CTL0 |= ADC12ENC;                             // Enable conversions
    /* ADC12+中断使能*/
    
 //   ADC12IE = 0x20;
    
    ADC12CTL0 |= ADC12SC;  
    
}
void ADC_getValue(void)
{
    //measure ADC value
    ADC12IE = 0x20;                                    // Enable interrupt
    ADC12CTL0 |= ADC12SC;                              // Start sampling/conversion
   // __bis_SR_register(LPM4_bits + GIE);                // LPM0, ADC12_ISR will force exit
    ADC12IE = 0x00;                                    // Disable interrupt
}

/***************************************************************************//**
 * @brief Handles ADC interrupts.
 *
 *        Stores result of single ADC conversion for reading position of the scroll wheel.
 * @param  none
 * @return none
 ******************************************************************************/

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    switch (__even_in_range(ADC12IV, ADC12IV_ADC12IFG15))
    {
        // Vector  ADC12IV_NONE:  No interrupt
        case  ADC12IV_NONE:
            break;

        // Vector  ADC12IV_ADC12OVIFG:  ADC overflow
        case  ADC12IV_ADC12OVIFG:
            break;

        // Vector  ADC12IV_ADC12TOVIFG:  ADC timing overflow
        case  ADC12IV_ADC12TOVIFG:
            break;

        // Vector  ADC12IV_ADC12IFG0: ADC12IFG0:
        case  ADC12IV_ADC12IFG0:
            
            break;

        // Vector  ADC12IV_ADC12IFG1:  ADC12IFG1
        case  ADC12IV_ADC12IFG1:
            break;

        // Vector ADC12IV_ADC12IFG2:  ADC12IFG2
        case ADC12IV_ADC12IFG2:
            break;

        // Vector ADC12IV_ADC12IFG3:  ADC12IFG3
        case ADC12IV_ADC12IFG3:
            break;

        // Vector ADC12IV_ADC12IFG4:  ADC12IFG4
        case ADC12IV_ADC12IFG4:
            break;

        // Vector ADC12IV_ADC12IFG5:  ADC12IFG5
        case ADC12IV_ADC12IFG5:
          //  ADC_Result1++;
          /*   ceshi++;
            if(ceshi == 10000)
            {
              ceshi = 0;
              ceshi1++;
              if(ceshi1==1000) ceshi1 = 0;
            }
           */ 
            ADC_Result1 =ADC12MEM4;                  // ADC12MEM = A0 > 0.5AVcc?
            ADC_Result = ADC12MEM5;                  // ADC12MEM = A0 > 0.5AVcc?
            __bic_SR_register_on_exit(LPM0_bits);      // Exit active CPU
            break;

        // Vector ADC12IV_ADC12IFG6:  ADC12IFG6
        case ADC12IV_ADC12IFG6:
            break;

        // Vector ADC12IV_ADC12IFG7:  ADC12IFG7
        case ADC12IV_ADC12IFG7:
            break;

        // Vector ADC12IV_ADC12IFG8:  ADC12IFG8
        case ADC12IV_ADC12IFG8:
            break;

        // Vector ADC12IV_ADC12IFG9:  ADC12IFG9
        case ADC12IV_ADC12IFG9:
            break;

        // Vector ADC12IV_ADC12IFG10:  ADC12IFG10
        case ADC12IV_ADC12IFG10:
            break;

        // Vector ADC12IV_ADC12IFG11:  ADC12IFG11
        case ADC12IV_ADC12IFG11:
            break;

        // Vector ADC12IV_ADC12IFG12:  ADC12IFG12
        case ADC12IV_ADC12IFG12:
            break;

        // Vector ADC12IV_ADC12IFG13:  ADC12IFG13
        case ADC12IV_ADC12IFG13:
            break;

        // Vector ADC12IV_ADC12IFG14:  ADC12IFG14
        case ADC12IV_ADC12IFG14:
            break;

        // Vector ADC12IV_ADC12IFG15:  ADC12IFG15
        case ADC12IV_ADC12IFG15:
            break;

        default:
            break;
    }
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
