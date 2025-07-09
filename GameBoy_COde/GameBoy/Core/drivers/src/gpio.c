
/**
*@file gpio.c
*@brief GPIO driver implementation for STM32F4xx MCUs.
*
*@author GameBoy Project
*@date 2025
*/

#include "gpio.h"

/***********************************************************************
Initialize GPIO pin directly
***********************************************************************/
void GPIO_init_direct(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode, uint8_t speed, uint8_t type, uint8_t pupd, uint8_t af)
{
    // Enable GPIO clock
    if(GPIOx == GPIOA) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    } else if(GPIOx == GPIOB) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    } else if(GPIOx == GPIOC) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    } else if(GPIOx == GPIOF) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    }
    
    // Configure mode
    GPIOx->MODER &= ~(3U << (pin * 2));
    GPIOx->MODER |= (mode << (pin * 2));
    
    // Configure speed
    GPIOx->OSPEEDR &= ~(3U << (pin * 2));
    GPIOx->OSPEEDR |= (speed << (pin * 2));
    
    // Configure output type
    GPIOx->OTYPER &= ~(1U << pin);
    GPIOx->OTYPER |= (type << pin);
    
    // Configure pull-up/pull-down
    GPIOx->PUPDR &= ~(3U << (pin * 2));
    GPIOx->PUPDR |= (pupd << (pin * 2));
    
    // Configure alternate function (if needed)
    if(af != 0) {
        if(pin < 8) {
            GPIOx->AFR[0] &= ~(0xF << (pin * 4));
            GPIOx->AFR[0] |= (af << (pin * 4));
        } else {
            GPIOx->AFR[1] &= ~(0xF << ((pin - 8) * 4));
            GPIOx->AFR[1] |= (af << ((pin - 8) * 4));
        }
    }
}