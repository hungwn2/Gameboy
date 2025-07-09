/**
*@file gpio.h
*@brief GPIO driver header for STM32F4xx MCUs.
*
*@author GameBoy Project
*@date 2025
*/

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "main.h"
#include "stm32f4xx.h"


void GPIO_init_direct(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode, uint8_t speed, uint8_t type, uint8_t pupd, uint8_t af);

#endif



