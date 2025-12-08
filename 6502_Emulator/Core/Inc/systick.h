/*
 * systick.h
 *
 *  Created on: Nov 6, 2025
 *      Author: henryhungwy
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_
#include <stdbool.h>
#include <stdint.h>
void systick_init(uint32_t sys_freq);
uint32_t systick_get_ms(void);
void systick_handler(void);
#endif /* INC_SYSTICK_H_ */
