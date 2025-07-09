/*
 * adc.h
 *
 *  Created on: May 6, 2025
 *      Author: User
 */

#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include "main.h"

void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif