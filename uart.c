#include "tm4c123gh6pm.h"
#include "stdint.h"

#define GPIO_PE45_M 0x30

void UART0_Init(void){
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	
	UART5_CTL_R &= ~UART_CTL_UARTEN;
	UART5_IBRD_R = 520;    
  UART5_FBRD_R = 53;
	UART5_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART5_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
	GPIO_PORTE_AFSEL_R |= GPIO_PE45_M;
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFF00FFFF) | (GPIO_PCTL_PE5_U5TX | GPIO_PCTL_PE4_U5RX);
	GPIO_PORTE_DEN_R |= GPIO_PE45_M;
}

uint8_t UART0_Available(void){
	return ((UART5_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

uint8_t UART0_Read(void){
	while(UART0_Available() != 1);
	return (uint8_t)(UART5_DR_R&0xFF);
}

void UART0_Write(uint8_t data){
	while((UART5_FR_R&UART_FR_TXFF) != 0);
	UART5_DR_R = data;
}
