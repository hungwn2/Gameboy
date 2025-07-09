#ifndef JOYSTICK_H
#define JOYSTICK_H


#include "stm32f4xx.h"
#include "../adc.h"
#include "../gpio.h"
#include <stdint.h>

#define JOY_THRESHOLD_HIGH  2500
#define JOY_THRESHOLD_LOW   1500

typdef enum{
    JOY_CENTER=0,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT,
    JOY_UP_LEFT,
    JOY_UP_RIGHT,
    JOY_DOWN_LEFT,
    JOY_DOWN_RIGHT
}JOY_Direction_t;


typdef struct{
    uint16_t x_raw;
    uint16_t y_raw;
    JOY_Direction_t direction;
}JOY_STATE_t;

void JOY_Init(void);
void JOY_Read(JOY_State_t *state);

#endif