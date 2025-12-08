/*
 * button.h
 *
 *  Created on: Nov 24, 2025
 *      Author: henryhungwy
 */

#ifndef DRIVERS_INC_BUTTON_H_
#define DRIVERS_INC_BUTTON_H_
#include "../../peripherals/gpio.h"
#include <stdint.h>


#define BTN_UP 0
#define BTN_DOWN 1
#define BTN_LEFT 2
#define BTN_RIGHT 3

uint8_t buttons_read(void);


#endif /* DRIVERS_INC_BUTTON_H_ */
