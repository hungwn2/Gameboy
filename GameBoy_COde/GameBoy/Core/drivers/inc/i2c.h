/**
*@file stm32f407xx_i2c.h
*@brief provide APIs for I2C communications.
*
*This header file provide APIs for communication between stm32f407xx MCU and I/O devices through I2C protocol.
*
*@author Tran Thanh Nhan
*@date 31/07/2019
*/

#ifndef STM32F407XX_I2C_H
#define STM32F407XX_I2C_H

#include "stm32f4xx.h"                  // Device header
// #include "stm32f407xx_common_macro.h"
// #include "stm32f407xx_rcc.h"
#include <stdint.h>
#include <stdlib.h>


typedef struct{
    uint32_t clockSpeed;
    uint8_t ownAddress1;
    uint8_t addrssingMode;
    uint8_t dualAddressMode;
    uint8_t ownAddress2;
    uint8_t generalCallMode;
    uint8_t noStretchMode;
}I2C_Config_t;


typedef struct{
    I2C_TypeDef *instance;
    I2C_Config_t config;
}I2C_Handle_t;


void I2C_PeriClockControl(I2C_TypeDef *pI2Cx, uint8_t EnOrDi);
void I2C_Init(I2C_Typedef *pI2Cx, uint8_t EnOrDi);

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_TypeDef *pI2Cx);
void I2C_MasterSendData(I2C_Handle_t *pI2cHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr);



void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);
#endif