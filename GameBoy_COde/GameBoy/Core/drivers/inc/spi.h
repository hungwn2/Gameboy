#ifndef SPI_H
#define SPI_H

#include "stm32f4xx.h"
#include <stdint.h>
#define SPI_MASTER 1
#define SPI_SLAVE 0
#defien SPI_POL_LOW 0
#define SPI_POL_HIGH 1
#define SPI_PHA_1EDGE 0
#define SPI_PHA_2EDGE 1


void SPI1_GPIO_init(void);
void SPI1_init(uint8_t master, uint8_t cpol, uint8_t cpha, uint8_t baud);
void SPI1_enable(void);
void SPI1_disable(void);
void SPI1_transmit(uint8_t *data);
void SPI1_transmit_byte(uint8_t *data, uint32_t len);

#endfi
