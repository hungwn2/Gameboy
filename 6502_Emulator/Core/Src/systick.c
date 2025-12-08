/*
 * systick.c
 *
 *  Created on: Nov 6, 2025
 *      Author: henryhungwy
 */


#include "systick.h"
#include "stm32c0xx.h"

#define CTRL_ENABLE (1U<<0)
#define CTRL_TICKINT (1U<<1)
#define CTRL_CLKSRC (1U<<2)


static volatile uint32_t g_ms_ticks = 0;


void systick_init(uint32_t sys_freq) {

    uint32_t reload_val = (sys_freq / 1000U) - 1U;

    SysTick->LOAD = reload_val;

    SysTick->VAL = 0U;

    SysTick->CTRL = CTRL_CLKSRC | CTRL_TICKINT | CTRL_ENABLE;
}

uint32_t systick_get_ms(void) {
    // Return the volatile tick count
    return g_ms_ticks;
}

void systick_handler(void) {
    g_ms_ticks++;
}
