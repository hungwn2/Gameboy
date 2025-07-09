/*
 * uart.h
 *
 *  Created on: Jul 7, 2025
 *      Author: User
 */

#ifndef DRIVERS_INC_UART_H_
#define DRIVERS_INC_UART_H_

#include <stdint.h>
#include <stddef.h>

#define UART_BAUD_9600 9600U
#define UART_BAUD_115200 115200U



void UART_inti(USART_TypeDef *UARTx, uint32_t baudrate);
void UART_write(USART_TypeDef *UARTx, uint32_t data);
uint8_t UART_read(USART_TypeDef *UARTx);
void UART_print(USART_TypeDef *UARTx, const char *str);


//next add dma

#endif /* DRIVERS_INC_UART_H_ */
