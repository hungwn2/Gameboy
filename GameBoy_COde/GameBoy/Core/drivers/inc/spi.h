/*
 * spi.h
 *
 *  Created on: Jun 15, 2025
 *      Author: User
 */


/*
 * spi.c
 *
 *  Created on: Jun 15, 2025
 *      Author: User
 */


#pragma once

#include "stm32f4xx.h"

typedef struct{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
}SPI_Config_t;

typedef struct{
    SPI_TypeDef *pSPIx;
    SPI_Config_t SPIConfig;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint8_t TxLen;
    uint8_t RxLen;
    uint8_t TxState;
    uint8_t RxState;
} SPI_Handle_t;


#define SPI_DEVICE_MODE_MASTER    1
#define SPI_DEVICE_MODE_SLAVE     0


#define SPI_BUS_CONFIG_FD         1  // Full duplex
#define SPI_BUS_CONFIG_HD         2  // Half duplex
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 3



//baud rate divider
#define SPI_SCLK_SPEED_DIV2       0
#define SPI_SCLK_SPEED_DIV4       1
#define SPI_SCLK_SPEED_DIV8       2
#define SPI_SCLK_SPEED_DIV16      3
#define SPI_SCLK_SPEED_DIV32      4
#define SPI_SCLK_SPEED_DIV64      5
#define SPI_SCLK_SPEED_DIV128     6
#define SPI_SCLK_SPEED_DIV256     7

//data frame format
#define SPI_DFF_8BITS             0
#define SPI_DFF_16BITS            1

//clock polarity 
#define SPI_CPOL_HIGH             1
#define SPI_CPOL_LOW              0

//spi clock phae
#define SPI_CPHA_HIGH             1
#define SPI_CPHA_LOW              0

#define SPI_SSM_EN                1
#define SPI_SSM_DI                0

/* SPI states */
#define SPI_READY                 0
#define SPI_BUSY_IN_RX            1
#define SPI_BUSY_IN_TX            2

/* SPI application events */
#define SPI_EVENT_TX_CMPLT        1
#define SPI_EVENT_RX_CMPLT        2
#define SPI_EVENT_OVR_ERR         3


void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t EnOrDi);
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_TypeDef *pSPIx);

void SPI_SendData(SPI_TypeDef *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_TypeDef *pSPIx, uint8_t *pRxBuffer, uint32_t Len);
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_ISRHandling(SPI_Handle_t *pHandle);

/*
 * Application callback
 */
void SPI_ApplicationEventCallback(SPI_Handle_t *pHandle, uint8_t AppEv);