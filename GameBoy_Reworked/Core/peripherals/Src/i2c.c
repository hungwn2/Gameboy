/*
 * i2c.c
 *
 *  Created on: Nov 27, 2025
 *      Author: henryhungwy
 */
#include "stm32f4xx.h"


#define GPIOBEN (1U<<1)
#define I2C1EN  (1U<<21)
#define I2C1_100KHZ 80
#define CR1_PE 	(1U<<0)

#define SR2_BUSY	(1U<<1)
#define CR1_START	(1U<<8)
#define SR1_SB		(1U<<0)
#define SR1_ADDR 	(1U<<1)
#define SR1_TXE 	(1)
