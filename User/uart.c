/*
 * uart.c
 *
 *  Created on: 2021年11月6日
 *      Author: Lenovo
 */

#include "uart.h"
#include "gpio.h"
// 此处修改串口 P3.3 P3.4
void UART0_INIT(void)
{
P3SEL |= BIT3 + BIT4;
UCA0CTL1 |= UCSWRST;
UCA0CTL0 = UCMODE_0;
UCA0CTL0 &= ~UC7BIT;
UCA0CTL1 |= UCSSEL_1;

UCA0CTL1 = UCSWRST + UCSSEL__SMCLK + UCRXEIE;
UCA0BRW = 4000000 / 9600; //默认波特率

//UCA0BR0 = 0X16;
//UCA0BR1 = 0X04;
//UCA0MCTL = 0X54;
UCA0CTL1 &= ~UCSWRST;
UCA0IE |= UCRXIE;
//_BIS_SR(GIE);
_EINT();
}
   void UART0_Sendchar(unsigned char Data)
{
while((UCA0IFG & UCTXIFG)==0);
UCA0TXBUF = Data;
}


void UART0_Sendint(long int Data)
{
if(Data<0)
{
Data = -Data;
UART0_Sendchar('-');
}
if(Data<10)
{
UART0_Sendchar(Data + '0');
}
else if((10<=Data)&&(Data<100))
{
UART0_Sendchar(Data/10 + '0');
UART0_Sendchar(Data%10 + '0');
}
else if((100<=Data)&&(Data<1000))
{
UART0_Sendchar(Data/100 + '0');
UART0_Sendchar(Data/10%10 + '0');
UART0_Sendchar(Data%10 + '0');
}
else if((1000<=Data)&&(Data<10000))
{
UART0_Sendchar(Data/1000 + '0');
UART0_Sendchar(Data/100%10 + '0');
UART0_Sendchar(Data/10%10 + '0');
UART0_Sendchar(Data%10 + '0');
}
else if((10000<=Data)&&(Data<100000))
{
UART0_Sendchar(Data/10000 + '0');
UART0_Sendchar(Data/1000%10 + '0');
UART0_Sendchar(Data/100%10 + '0');
UART0_Sendchar(Data/10%10 + '0');
UART0_Sendchar(Data%10 + '0');
}
}