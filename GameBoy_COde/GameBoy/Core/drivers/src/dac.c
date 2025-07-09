#include "adc.h"
#include "stm32f4xx.h"

#define ENABLE 1
#define DISABLE 0
#define ON 1
#define OFF 0


void DAC_init_channel(uint8_t channel){
    RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;

    if (channel==1){
        GPIOA->MODER|=(3U<<(4*2));
    }
    else if (channel==2){
        GPIOA->MODER|=(3U<<(5*2));
    }

    RCC->APB1ENR|=RCC_APB1ENR_DACEN;


    if (channel==1){
        DAC->CR|=DAC_CR_EN1;
    }
    else if(channel==2){
        DAC->CR|=DAC_CR_EN2;
    }
}


void DAC_write(uint8_t channel, uint16_t value){

    if (value>0xfff) value=0xfff;
    
}
