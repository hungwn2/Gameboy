/*
 * bus.h
 *
 *  Created on: Nov 6, 2025
 *      Author: henryhungwy
 */

#ifndef INC_BUS_H_
#define INC_BUS_H_

#include <stdint.h>

void bus_reset(void);

uint8_t bus_read(uint16_t addr);

void bus_write(uint16_t addr, uint8_t value);


#endif /* INC_BUS_H_ */
