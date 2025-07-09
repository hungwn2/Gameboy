/*
 * adc.c
 *
 *  Created on: May 6, 2025
 *      Author: User
 */


#include <stdint.h>

 #include "adc.h"

 #define ENABLE 1
 #define DISABLE 0
 #define ON 1
 #define OFF 0

#define CR2_ADCON (1U<<0)
#define CR2_CONT (1U<<1)
#define CR2_SWSTART (1U<<30)
#define SR_EOC (1U<<1)



 static void ADC_configure_channel(ADC_TypeDef *ADCxPtr, uint8_t channel){
    ADCxPtr->SQR1 &=~ADC_SQR1_L;
    //clear conversion seq length
    ADCxPtr->SQR3 &=~ADC_SQR3_SQ1;
    //clear first postion
    ADCxPtr->SQR3|=(channel<<ADC_SQR_SQ1_Pos);
    //set sq1 to desired channel
}

static void ADC_channel_gpio_init(uint8_t channel, ADC_TypeDef *ADCxPtr){
    GPIO_TypeDef *port;
    uint8_t port;

    switch (channel){
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        port=GPIOA; pin=channel; break;
        case 8: case 9:
        port=GPIOB; pin=channel-8; break;
        case 10: case 11: case 12: case 13: case 14 :case 15:
        port=GPIOC; pin=channel-10; break;
        default:
        return;
    }
    GPIO_init_direct(port, pin, GPIO_MODE_ANL, GPIO_OUTPUT_LOW_SPEED, GPIO_OUTPUT_TYPE_PP, GPIO_PU, 0);
}


void ADC_CLK_Ctr(ADC_TypeDef *ADCxPtr, uint8_t enOrDis){
    if (enOrDis==ENABLE){
        if (ADCxPtr==ADC1) RCC->APB2ENR=RCC_APB2ENR_ADC1EN;
        else if (ADCxPtr==ADC2) RCC->APB2ENR|=RCC_APB2ENR_ADC2EN;
        else if (ADCxPtr==ADC3) RCC->APB2ENR|=RCC_APB2ENR_ADC3EN;
    }else{
        if (ADCxPTR==ADC1) RCC->APB2ENR &=~ RCC_APB2ENR_ADC1EN;
        else if (ADCxPTR==ADC2) RCC->APB2ENR &=~ RCC_APB2ENR_ADC2EN;
        else if (ADCxPTR==ADC3) RCC->APB2ENR &=~ RCC_APB2ENR_ADC3EN;
    }
}

void ADC_ctr(ADC_TypeDef *ADCxPtr, uint8_t onOrOff){
    if (onOrOff==ON) ADCxPtr->Cr2|=ADC_CR2_ADON;
    else ADCxPtr->CR2 &=~ADC_CR2_ADON;
}

void ADC_init_channel(ADC_TypeDef* ADCxPtr, uint8_t channel){
    ADC_channel_gpio_iinit(channel, ADCxPtr);
    static ADC_Config_t ADCxConfig={
        .numOfConversion=1,
        .resolution=ADC_RES_12_bits,
        .conversionMode=ADC_CVSMODE_SINGLE
    };

    ADC_Handle_t ADCxHandle={
        .ADCxPtr=ADCxPtr,
        .ADCxConfigPtr=&ADCxConfig
    };
    ADC_init(&ADCxHandle);
}


void ADC_deinit(void){
    RCC->APB2RSTR |= RCC_APB2RSTR_ADCRST;
    RCC->APB2RSTR&=~RCC_APB2RSTR_ADCRST;

}

void start_conversion(void){
	ADC1->CR2|=ADC_CR2_CONT;
	//Continuous Conversion
	ADC1->CR2|=ADC_CR2_SWSTART;
	//Start ADC Conversion
}


uint16_t ADC_read(ADC_TypeDef *ADCxPtr, uint8_t channel) {
    uint16_t timeOut = 0xFFF;
    ADC_configure_channel(ADCxPtr, channel);
    ADCxPtr->CR2 |= ADC_CR2_SWSTART;
    while (!(ADCxPtr->SR & ADC_SR_EOC)) {
        if (--timeOut == 0) return 0;
    }
    return ADCxPtr->DR;
}

uint32_t adc_read(void){
	return ADC_read(ADC1, 1);
}

