/*
 * gpio.c
 *
 *  Created on: Oct 12, 2025
 *      Author: henryhungwy
 */


#include "gpio.h"
#include "stm32c0xx.h"

#define GPIOAEN (1U<<0)
#define MODER5_MASK (3U<<10)
#define MODER5_OUT (1u<<10)


#define BSRR_SET5    (1U<<5)  // (1U << 5)
#define BSRR_RESET5  (1U<<(5+16))  // (1U << 21)
#include <stdint.h>

void led_init(void){
	RCC->IOPENR|=GPIOAEN;
	 GPIOA->MODER &= ~MODER5_MASK; // Clear bits
    GPIOA->MODER |= MODER5_OUT;
}

void gpio_write_led(bool state) {
    if (state) {
        // Set PA5 high
        GPIOA->BSRR = BSRR_SET5;
    } else {
        // Set PA5 low
        GPIOA->BSRR = BSRR_RESET5;
    }
}
