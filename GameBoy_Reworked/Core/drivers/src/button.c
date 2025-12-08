/*
 * button.c
 *
 *  Created on: Nov 24, 2025
 *      Author: henryhungwy
 */

#include "button.h"

uint8_t button_read(void)
{
	uint8_t state=0;
	if (GPIOB->IDR && (1U<<3)) return BTN_UP;
	if (GPIOB->IDR && (1U<<4)) return BTN_LEFT;
	if (GPIOB->IDR && (1U<<5)) return BTN_RIGHT;
	if (GPIOA->IDR && (1U<<15)) return BTN_DOWN;

}
