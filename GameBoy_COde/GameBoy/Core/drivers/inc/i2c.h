/**
*@file i2c.h
*@brief Provide APIs for I2C communication.
*
*This header file provides functions for interfacing with I2C peripherals
*on the STM32F401RE, suitable for your Mario game system (e.g., screen, sensors).
*
*@author Henry
*@date July 7, 2025
*/

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"
#include <stdint.h>

/***********************************************************************
Macro definitions
***********************************************************************/
#define I2C_WRITE 0
#define I2C_READ  1

#define I2C_ACK_ENABLE  1
#define I2C_ACK_DISABLE 0

/***********************************************************************
Function prototypes
***********************************************************************/
void I2C_init(I2C_TypeDef *I2Cx);
void I2C_start(I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction);
void I2C_write(I2C_TypeDef *I2Cx, uint8_t data);
uint8_t I2C_read_ack(I2C_TypeDef *I2Cx);
uint8_t I2C_read_nack(I2C_TypeDef *I2Cx);
void I2C_stop(I2C_TypeDef *I2Cx);
void I2C_GPIO_init(I2C_TypeDef *I2Cx);

#endif /* I2C_H_ */
