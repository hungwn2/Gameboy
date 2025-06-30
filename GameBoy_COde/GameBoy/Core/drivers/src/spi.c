

#include "spi.h"


void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t EnOrDi){
     if (EnOrDi==ENABLE){
        if (pSPIX ==SPI1) RCC->APB2ENR|=(1<<12);
        else if(pSPIx==SPI2) RCC->APB1ENR|=(1<<14);
     }
     else{
        if (pSPIx == SPI1) RCC->APB2ENR &=~(1<<12);
        else if(pSPIx==SPI2) RCC->APB1ENR|=(1<<14);
     }
}

void SPI_Init(SPI_Handle_t *pSPIHandle){
    
}
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