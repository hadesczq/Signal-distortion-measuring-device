/*
 * uart.h
 *
 *  Created on: 2021��11��6��
 *      Author: Lenovo
 */

#ifndef UART_H_
#define UART_H_

#include "msp430f5529.h"


void UART0_INIT(void);
void UART0_Sendchar(unsigned char Data);

#endif /* UART_H_ */
