/*
 * mario_engine.c
 *
 *  Created on: Jul 8, 2025
 *      Author: User
 */


#include "mario_engine.h"


Mario_object_t Mario;
Obstacle_t blocks[256];



void RTE_init(void){
	RCC_set_SYSCLK_PLL_84_MHz();
	RNG_init();
	ILI9341_init();
	ILI9341_rotate(ILI9341_orientation_landscape);
	ILI9341_fill_display;



}
void RTE_start_update_frame(void){
	TIM_ctr(TIM6, START);
}
