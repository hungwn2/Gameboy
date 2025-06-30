#include "adc_dma.h"
#define GPIOAEN (1U<<0)
#define ADC1EN (1U<<8)
#define CR1_SCANE (1U<<8)
#define CR2_DMA (1U<<8)
#define CR2_DDS (1U<<9)
#define CR2_CONt (1U<<1)
#define CR2_ADCON (1U<<0)
#define CR2_ADCON (1U<<0)
#define CR2_SWSTART (1U<<30)
#define DMA2EN (1U<<22)
#define DMA_SCR_EN (1U<<0)
#define DMA_SCR_MINC (1U<<10)
#define DMA_SCR_PINC (1U<<9)
#define DMA_SCR_CIRC (1U<<8)
#define DMA_SCR_TCIE (1U<<4)
#define DMA_SCR_TEIE (1U<<2)
#define DMA_SFCR_DMDIS (1U<<2)


uint16_t adc_raw_data[NUM_OF_CHANNELS];

void adc_dma_init(void){
    RCC->AHB1ENR|=GPIOAEN;
    GPIOA->MODER|=(1U<<0);
    GPIOA->MODER|=(1U<<1);
    GPIOA->MODER|=(1U<<2);
    GPIOA->MODER|=(1U<<3);


    RCC->APB2ENR|=ADC1EN;
    ADC1->SQR1|=(1U<<20);
    ADC1->SQR1&=~(1U<<21);
    ADC1->SQR1 &=~(1U<<22);
    ADC1->SQR1 &=~(1U<<23);


    ADC1->SQR3= (0<<0) | (1U<<5);

    ADC1->CR1=CR1_SCAN;
    ADC1->CR2|=CR2_CONT|CR2_DMA|CR2_DDS;
    RCC->AHB1ENR|=DMA2EN;
    DMA2_Stream0->Cr &=~DMA_SCR_EN;
    while (DMA2_Stream0->CR & DMA_SCR_EN){}

    DMA2_Stream0->CR|=DMA_SCR_CIRC;
    DMA2_Stream0->CR|=(1U<<13);
    DMA2_Stream0->CR&=~(1U<<14);
    DMA2_Stream0->CR|=(1U<<11);
    DMA2_Stream0->Cr&=~(1U<<12);

    DMA2_Stream0->Cr|=DMA_SCR_MINC;
//periph+mem address
    DMA2_Stream0->PAR=(uint32_t)(&(ADC1->DR));
    DMA2_Stream0->MOAR=(uint32_t)(&adc_raw_data);


    DMA2_Stream0->NDTR=(uint16_t)NUM_OF_CHANNELS;
    DMA2_Stream0->CR|=DMA_SCR_EN;
    //enable dma stream

    ADC1->CR2|=CR2_ADCON;
    ADC1->CR2|=CR2_SWSTART;
}