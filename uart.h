#ifndef _UART_H_
#define	_UART_H_

#include "stdint.h"

void UART0_Init(void);

uint8_t UART0_Available(void);

uint8_t UART0_Read(void);

void UART0_Write(uint8_t data);

#endif // _UART_H_
