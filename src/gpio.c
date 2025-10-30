/*
 * gpio.c
 *
 *  Created on: Oct 12, 2025
 *      Author: henryhungwy
 */


#include "gpio.h"

#define GPIOAEN (1U<<0)
#define LED_BS5 (1U<<5)
#define LED_BR5 (1U << (5+16))

#include <stdint.h>

void led_init(void){
	RCC->IOPENR|=GPIOAEN;
	GPIOA->MODER &=~((1U<<11)|(1U<<10));
	GPIOA->MODER |=(1U<<10);
}

void led_on(void){
	GPIOA->BSRR=LED_BS5;
}

void led_off(void){
	GPIOA->BSRR=LED_BR5;
}
