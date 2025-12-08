/*
 * gpio.h
 *
 *  Created on: Nov 13, 2025
 *      Author: henryhungwy
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_


void gpio_init(uint16_t pin){
	RCC->IOPENR|=GPIOAEN;
	RCC->IOPENR|=GPIOBEN;
	GPIOA->MODER &= ~(3U << pin); // Clear bits
    GPIOA->MODER &= ~(3U << (15*2));
    GPIOA->PUPDR &= ~(3U << (15*2));
    GPIOA->PUPDR |=  (1U << (15*2));

    /* PB3, PB4, PB5 = inputs w/ pull-up */
    GPIOB->MODER &= ~((3U<<(3*2)) | (3U<<(4*2)) | (3U<<(5*2)));
    GPIOB->PUPDR &= ~((3U<<(3*2)) | (3U<<(4*2)) | (3U<<(5*2)));
    GPIOB->PUPDR |=  ((1U<<(3*2)) | (1U<<(4*2)) | (1U<<(5*2)));
}


void gpio_toggle(uin)


#endif /* INC_GPIO_H_ */
