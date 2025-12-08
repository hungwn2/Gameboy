/*
 * joystic.h
 *
 *  Created on: Nov 21, 2025
 *      Author: henryhungwy
 */

#ifndef DRIVERS_INC_JOYSTICK_H_
#define DRIVERS_INC_JOYSTICK_H_

#include "stm32f4xx.h"
#include "../../peripherals/inc/adc.h"
#include "../../peripherals/inc/gpio.h"


/*
 * Joystick Thresholds
 */
#define X_POS_THRES_L 2000
#define X_POS_THRES_H 2150
#define Y_POS_THRES_L 2000
#define Y_POS_THRES_H 2150

/*
*X axis and Y axis direction
*/
#define X_DIR_LEFT -1
#define X_DIR_RIGHT 1
#define X_DIR_CENTER 0
#define Y_DIR_UP 1
#define Y_DIR_DOWN -1
#define Y_DIR_CENTER 0
/*
*Joystick direction
*/
#define JS_DIR_LEFT_UP 1
#define JS_DIR_LEFT_DOWN 2
#define JS_DIR_LEFT 3
#define JS_DIR_RIGHT_UP 4
#define JS_DIR_RIGHT_DOWN 5
#define JS_DIR_RIGHT 6
#define JS_DIR_UP 7
#define JS_DIR_DOWN 8
#define JS_DIR_CENTERED 0


void joystick_init(uint8_t X_axis_ADC_channel, uint8_t Y_axis_ADC_channel);
uint8_t joystick_read_direction(uint8_t X_axis_ADC_channel, uint8_t Y_axis_ADC_channel);




#endif /* DRIVERS_INC_JOYSTICK_H_ */
