/*
 * uart.h
 *
 * Bare-metal UART driver for USART2 (PA2) for STM32C0.
 */

#ifndef UART_H
#define UART_H

#include <stdint.h>


void uart_init(uint32_t periph_clk);


void uart_write_byte(int ch);


void uart_write_string(const char* str);

#endif // UART_H
