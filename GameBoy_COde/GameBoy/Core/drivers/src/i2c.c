/*
 * i2c.c
 *
 *  Created on: Jun 15, 2025
 *      Author: User
 */


#include "i2c.h"


void I2C_PeripheralClockControl(I2C_TypeDef *pI2Cx, uint8_t EnOrDi){
    if (EnOrDi==DISABLE){
        if (pI2C==I2C1)\ RCC->APB1ENR|=RCC_APB1ENR_I2CEN;
        else if (pI2Cx==I2C2) RCC->APB1ENR|=RCC_APB1ENR_I2C2EN;
        else if (pI2C==I2C3) RCC->APB1ENR |=RCC_APB1ENR_I2C3EN;
    }
    else{
        if (pI2C ==I2C1) RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
        else if (pI2Cx==I2C2) RCC->APB1ENR &=~RCC_APB1ENR_I2C_2EN;
        else if (pI2Cx==I2C3) RCC->APB1ENR &=~RCC_APB1ENR_I2C_3EN;
    }
}

void I2C_Init(I2C_Handle_t *pI2cHandle){
    uint32_t tempreg=0;
    I2C_PeripheralClockControl(pI2CHandle->pI2Cx, ENABLE);
    pI2CHandle->pI2Cx->CR1|=I2C_CR1_SWRST;
    pI2CHandle->pI2Cx->CR1 &=~I2C_Cr1_SWRST;

    tempreg=80;
    pI2CHandle->pI2Cx->CCR=tempreg;
    //configure clock control (16mhz, 100khz scl)

    pI2CHandle->pI2Cx->TRISE=17;

    pI2CHandle->pI2Cx->CR2=16;
    pI2CHandle->pI2Cx->CR1|=I2C_CR1_ACK;   
}

void I2C_MasterSendData(I2C_Handle_t *pI2cHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr){

    pI2CHandle->pI2Cx->Cr1|=(1<<I2C_CR1_START);
    //generate start cond
    while (!(pI2cHandle->pI2Cx->SR1 & (1<<I2C_SR1_SB)));

    SlaveAddr=SlaveAddr<<1;
    pI2CHandle->pI2Cx->DR=SlaveAddr;

    while (!(pI2cHandle->pI2Cx->SR1 & (1<<I2C_SR1_ADDR)));
    //wait till addr set
    volatile uint32_t temp=pI2cHandle->pI2Cx->SR1l
    temp=pI2cHandle->pI2Cx->SR2;
    (void) temp;
    while(Len>0){
        while (!(pI2CHandle->pI2Cx->SR1 & (1<<I2C_SR1_TXE)));

        pI2cHandle->pI2Cx->DR=*pTxBuffer;
        pTxBuffer++;
        Len--;
        //write data bit by bit to dr
    }
    while(!(pI2CHandle->pI2Cx->SR1 & (1<<I2C_SR1_BTF)));

    pI2cHandle->pI2Cx->CR1|=(1<<I2C_CR1_STOP);

}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr);
