/*
 * tim.c
 *
 *  Created on: Nov 13, 2025
 *      Author: henryhungwy
 */


#include "../inc/tim.h"
#define TIM2EN (1U<<0)
#define CR1_CEN (1U<<0)

void time2_1hz_init(void){
	RCC->APB1ENR|=TIM2EN;
	TIM2->PSC=1600-1;
	TIM2->ARR=1000-1;
	TIM2->CNT=0;
	TIM2->CR1=CR1_CEN;
}




