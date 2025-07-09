
/**
*@file gpio.c
*@brief GPIO driver implementation for STM32F4xx MCUs.
*
*@author GameBoy Project
*@date25
*/


#include "spi.h"



void SPI_GPIO_init(void){
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &=~ ((3U<<(5*2))|(3U<<(7*2)));
	GPIOA->MODER|=((2U<<(5*2))|(2U<<7*2)));

	GPIOA->AFR[0]&=~((0xF<<(4*5))|(0x5<<(4*7)));
	GPIO->AFR[0] |=((0x5<<(4*5))|(0x5 <<(4*7)));

	GPIOA->OSPEEDR|=((3U<<(5*2))|(3U<<(7*2)));
	GPIOA->OTYPER &=~((1U<<5)|(1U<<7));
	GPIOA->PUPDR &= ~((3U<<(5*2))|(3U<<(7*2)));
}


void SPI1_init(uint8_t master, uint8_t cpol, uint8_t cpha, uint8_t baud){
	RCC->APB2ENR |=RCC_APB2ENR_SPIEN;
	SPI1->CR1=0;

	if (ma)
}


void SPI1_enable(void){
	SPI1->CR1|=SPI_CR1_SPE;
}

void SPI_DISABLE(void){
	SPI1->CR1 &=~SPI_CR1_SPE;
}


void SPI1_transmit_bytes(uint8_t *data, uint32_t len){
	for (uint32_t i=0; i<len; i++){
		SPI1_transmit(data[i]);
	}
}

void SPI_transmit(uint8_t data){
	while (!(SPI1->SR & SPI_SR_TXE));
	*((__IO uint8_t *)&SPI1->DR)= data;
	while (SPI->SR & SPI_SR_BSY);
}






