#ifndef BUS_H
#define BUS_H

#include <stdint.h>


void bus_init(void);

uint8_t bus_read(uint16_t addr);
void bus_write(uint16_t addr, uint8_t value);

#endif