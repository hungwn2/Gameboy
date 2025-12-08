/*
 * adc.h
 *
 *  Created on: Nov 13, 2025
 *      Author: henryhungwy
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdint.h>
#include "stm32f4xx.h"
void adc_init(void);
uint32_t adc_read(uint8_t channel);


#endif /* INC_ADC_H_ */
