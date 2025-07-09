/*
 * ili9341.h
 *
 *  Created on: Jul 8, 2025
 *      Author: User
 */

#ifndef INC_ILI9341_H_
#define INC_ILI9341_H_
#include <stdint.h>
#include "stm32f4xx.h"
#define ILI9341_WIDTH 240
#define ILI9341_HEIGHT 320


#define ILI9341_COLOR_BLACK       0x0000
#define ILI9341_COLOR_WHITE       0xFFFF
#define ILI9341_COLOR_RED         0xF800
#define ILI9341_COLOR_GREEN       0x07E0
#define ILI9341_COLOR_BLUE        0x001F
#define ILI9341_COLOR_YELLOW      0xFFE0
#define ILI9341_COLOR_CYAN        0x07FF
#define ILI9341_COLOR_MAGENTA     0xF81F
#define ILI9341_COLOR_ORANGE      0xFD20

#define ILI9341_CS_PORT GPIOB
#define ILI9341_CS_PIN 6


#define ILI9341_DC_PORT GPIOB
#define ILI9341_DC_PIN 7

#define ILI9341_RST_PORT GPIOB
#define ILI9341_RST_PIN 8

void ILI9341_init(void);
void ILI9341_send_command(uint8_t cmd);
void ILI9341_send_data(uint8_t data);
void ILI9341_send_data16(uint16_t data);

void ILI9341_set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void ILI9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void ILI9341_fill_screen(uint16_t color);
void ILI9341_draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void ILI9341_draw_char(uint16_t x, uint16_t y, char c, uint16_t fg, uint16_t bg);
void ILI9341_draw_string(uint16_t x, uint16_t y, const char *str, uint16_t fg, uint16_t bg);

void ILI9341_set_rotation(uint8_t rotation);


#endif /* INC_ILI9341_H_ */
