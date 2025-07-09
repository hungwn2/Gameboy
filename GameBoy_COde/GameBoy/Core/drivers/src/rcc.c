/*
 * rcc.c
 *
 *  Created on: Jul 6, 2025
 *      Author: User
 */




#include "rcc.h"

#define ENABLE 1
#define DISABLE 0

void RCC_GPIO_CLK_Ctrl(GPIO_TypeDef *port, uint8_t enOrDis){
	if (enOrDis==ENABLE){
		  if (port == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		  else if (port == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		  else if (port == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
		  else if (port == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	      else if (port == GPIOE) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;	}

else{
	 if (port == GPIOA) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
	 else if (port == GPIOB) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
	 else if (port == GPIOC) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
	 else if (port == GPIOD) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
	 else if (port == GPIOE) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
	 else if (port == GPIOH) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
}
}

void RCC_ADD_CLK_Ctrl(ADC_TypeDef* ADCxPtr, uint8_t enOrDis){
	 if (enOrDis == ENABLE) {
	        if (ADCxPtr == ADC1) RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	        else if (ADCxPtr == ADC2) RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	        else if (ADCxPtr == ADC3) RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
	    } else {
	        if (ADCxPtr == ADC1) RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN;
	        else if (ADCxPtr == ADC2) RCC->APB2ENR &= ~RCC_APB2ENR_ADC2EN;
	        else if (ADCxPtr == ADC3) RCC->APB2ENR &= ~RCC_APB2ENR_ADC3EN;
	    }
}

void RCC_reset_ADC(void){
	RCC->APB2RSTR|=RCC_AB2RSTR_ADCRST;
	RCC->APB2RSTR&=~RCC_APB2RSTR_ADCRST;
}

void RCC_MC01_config(uint8_t source, uint8_t prescaler){
	RCC->CFGR &=~(RCC_CFGR_MCO1| RCC_CFGR_MCO1PRE);
	RCC->CFGR|=(source<<RCC_CFGR_MCO1_Pos);
}

void RCC_set_SYSCLK_PLL_84MHz(void){
	RCC->CR|=RCC_CR_HSSEON;
	while (!RCC->Cr &! RCC_CR_HSERDY);

	 FLASH->ACR |= FLASH_ACR_LATENCY_2WS;
	    FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;

	    RCC->CFGR &= ~RCC_CFGR_HPRE;
	    RCC->CFGR &= ~RCC_CFGR_PPRE1;
	    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	    RCC->CFGR &= ~RCC_CFGR_PPRE2;

	    RCC->PLLCFGR = (4 << RCC_PLLCFGR_PLLM_Pos) | (168 << RCC_PLLCFGR_PLLN_Pos) |
	                   (0 << RCC_PLLCFGR_PLLP_Pos) | RCC_PLLCFGR_PLLSRC_HSE |
	                   (7 << RCC_PLLCFGR_PLLQ_Pos);

	    RCC->CR |= RCC_CR_PLLON;
	    while (!(RCC->CR & RCC_CR_PLLRDY));

	    RCC->CFGR &= ~RCC_CFGR_SW;
	    RCC->CFGR |= RCC_CFGR_SW_PLL;
	    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	    RCC->CR &= ~RCC_CR_HSION;

}
