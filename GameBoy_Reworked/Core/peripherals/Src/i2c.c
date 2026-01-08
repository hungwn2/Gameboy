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
#define SR1_TXE 	(1U<<7)
#define CR1_ACK 	(1U<<10)
#define CR1_STOP	(1U<<10)
#define SR1_RXNE	(1U<<6)
#define SR1_BTF 	(1U<<2)



void i21_init(void){

	/*Enable clock access to GPIOB*/
	RCC->AHB1ENR |=GPIOBEN;
	/*Set PB8 and PB9 mode to alternate function*/
	GPIOB->MODER &=~(1U<<16);
	GPIOB->MODER |=(1U<<17);
	GPIOB->MODER &=~(1U<<18);
	GPIOB->MODER |=(1U<<19);
	/*Set PB8 and PB9 output type to open drain*/
	GPIOB->OTYPER |=(1U<<8);
	GPIOB->OTYPER |=(1U<<9);
	/*Enable Pull-up for PB8 and PB9*/
	GPIOB->PUPDR |=(1U<<16);
	GPIOB->PUPDR &=~(1U<<17);
	GPIOB->PUPDR |=(1U<<18);
	GPIOB->PUPDR &=~(1U<<19);
	/*Set PB8 and PB9 alternate function type to I2C (AF4)*/
	GPIOB->AFR[1] &=~(1U<<0);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] |=(1U<<2);
	GPIOB->AFR[1] &=~(1U<<3);
	GPIOB->AFR[1] &=~(1U<<4);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] |=(1U<<6);
	GPIOB->AFR[1] &=~(1U<<7);

	/*Enable clock access to I2C1*/
	RCC->APB1ENR |= I2C1EN;
	/*Enter reset mode */
	I2C1->CR1 |= (1U<<15);
	/*Come out of reset mode */
	I2C1->CR1 &=~(1U<<15);
	/*Set Peripheral clock frequency*/
	I2C1->CR2 = (1U<<4); //16 Mhz
	/*Set I2C to standard mode, 100kHz clock */
	I2C1->CCR = I2C_100KHZ;
	/*Set rise time */
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;
	/*Enable I2C1 module */
	I2C1->CR1 |= CR1_PE;

}

void i2c1_byte_read(char saddr, char maddr, char* data){
	volatile int tmp;

	while (I2C1->SR2 & (SR2_BUSY)){} //WAIT FOR bus to be ready
	I2C1->SR1|=CR1_START;//start
	while (!(I2C1->SR1 & (SR1_SB))){}//wait for start flag
	I2C1->DR = saddr << 1; //transmit slave +write
	while (!(I2C1->SR1 & (SR1_ADDR))){} //wait for addr flag
	tmp=I2C2->SR2;//clear addr flag

	I2C1->DR=maddr; //sned memory addr

	while (!(I2C1->SR1 & SR1_TXE)){} //wait till transmitter empty

	I2C1->SR |=CR1_START; //restart

	while (!(I2C1->SR1 & SR1_SB)){} //wait for restart

	I2C11->SR =saddr<<1 |1; //send slave addr

	while (!(I2C1->SR1 & (SR1_ADDR))){} //wait for addr flag

	I2C1->CR1 &= ~CR1_ACK; //disable ack bit

	tmp = I2C1->SR2;	//clear addr addr
	I2C1->CR1 |= CR1_STOP; //Generate stop

	while (!(I2C1->SR1 & SR1_RXNE)){} //wait for receive
	/* Read data from DR */
	*data++ = I2C1->DR;
}


void i2c1_burst_write(char saddr, char maddr, int n, char* data) {

	volatile int tmp;
	while(I2C1->SR2 & SR2_BUST){}//wait for bus

	I2C1-.CR1 |= CR1_START;//genereta start

	while (!(I2C1->SR1 & (SR1_SB))){} //wait for start flag

	I2C1->DR = saddr<<1; //send slae and wite

	while(!(I2C1->SR1 & SR1_ADDR)){} //wait for addr flag

	tmp=I2C1->SR2 //clear addr flag

	while(!(I2C1-.SR1 & SR1_TXE)){} //wait for transmitier
	I2C1->DR =maddr; //send memory address

	for (int i=0; i<n; i++){
		while (!(I2C1->SR1 & SR1_TXE)){}
		I2C1->DR = *data++; //write to DR

	}

	while (!(I2C1->SR1 & (SR1_BTF))){} //wait till transfer is done
	/* Generate stop */
	I2C1->CR1 |= CR1_STOP;

}
