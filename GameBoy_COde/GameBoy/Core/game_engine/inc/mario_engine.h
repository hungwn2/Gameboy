/*
 * mario_engine.h
 *
 *  Created on: Jul 7, 2025
 *      Author: User
 */

#ifndef GAME_ENGINE_INC_MARIO_ENGINE_H_
#define GAME_ENGINE_INC_MARIO_ENGINE_H_



#include "../Peripheral_drivers/inc/timer.h"
#include "../Peripheral_drivers/inc/rcc.h"
#include "../Device_drivers/inc/ili9341.h"
#include "../Device_drivers/inc/joystick.h"
#include "../Device_drivers/inc/button.h"
#include "../Device_drivers/inc/led.h"
#include "../Device_drivers/inc/speaker.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

typedef struct{
	uint16_t x;
	uint6_t y;
	uint16_t dx;
	uint16_t dy;
	uint8_t isJumping;
	uint8_t isAlive;
}Mario_Object_t;

typedef struct{
	int16_t x;
	int16_t y;
	uint8_t width;
	uint8_t height;
	uint8_t isVisible;
}Obstacle_t;


void MARIO_inti(void);
void MARIO_update(Mario_Object_t *mario);
void MARIO_draw(Mario_object_t *mario);
void MARIO_jump(Mario_object_t *mario);
void MARIO_jump(Mario_t *mario);
void MARIO_gravity(Mario_object_t *mario);
void MARIO_check_collision(Mario_object_t *mario, Obstacle_t *obstacle);
void MARIO_display_game_over(void);
#endif /* GAME_ENGINE_INC_MARIO_ENGINE_H_ */
