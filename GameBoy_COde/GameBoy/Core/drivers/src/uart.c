/*
 * uart.c
 *
 *  Created on: Jul 7, 2025
 *      Author: User
 */


#include "stm32f4xx.h"
#include "../uart.h"
#include "rcc.h"

#define ENABLE 1
#define DISABLE 0


void UART_CLK_Ctrl(USART_TypeDef *UARTx, uint8_t enOrDis){
	if (enOrDis==ENABLE){
		if (UARTx==USART1) RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
		else if (UARTx==USART2) RCC->APB2ENR|=RCC_APB2ENR_USART2EN;
		else if (UARTx==USART3) RCC->APB2ENR|=RCC_APB2ENR_USART3EN;
	}
	else{
		if (UARTx==USART1) RCC->APB2ENR &=~RCC_APB2ENR_USART1EN;
		else if (UARTx==USART2) RCC->APB2ENR&=~RCC_APB2ENR_USART2EN;
		else if (UARTx==USART3) RCC->APB2ENR&=~RCC_APB2ENR_USART3EN;	}
}
}


void UART_init(USART_TypeDef *UARTx, uint32_t baudrate){
	UART_CLK_Ctrl(UARTx, ENABLE);
	RCC_GPIO_CLK_Ctrl(GPIOA, ENABLE);
	GPIOA->MODER &=~((3U<<(9*2))|(3U<<(10*2)));
	GPIO->MODER |= ((2U<<(9*2))|(2U<<(20*2)));
	GPIOA->AFR[1] &=~((0xF <<(9-8)*4))|(0xF <<((10-8)*4)));
    GPIOA->AFR[1] |= ((7 << ((9 - 8) * 4)) | (7 << ((10 - 8) * 4))); // AF7 (USART)
    UARTx->BRR=SystemCoreClock/baudrate;
    UARTx->CR1|=USART_CR1_TE+USART_CR1_RE;
    UARTx->CR1|=USART_CR1_UE;
}

void UART_write(USART_TypeDef *UARTx, uint8_t data){
	while(!(UARTx->SR & USART_SR_TXE));
	USART->DR=data;
}

void UART_print(USART_TypeDef *UARTx, const char* str){
	while (*str){
		UART_write(UARTx, *str++);
	}
}
