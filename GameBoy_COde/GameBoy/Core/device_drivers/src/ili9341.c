/*
 * ili9341.c
 *
 *  Created on: Jul 8, 2025
 *      Author: User
 */


#include "ili9341.h"

static void ili9341_HW_init(void){

}

static void ILI9341_send_command(uint8_t cmd);
static void ILI9341_send_data(uint8_t data);
static void ILI9341_send_data16(uint16_t data);


static void ILI9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
static void ILI9341_fill_screen(uint16_t color);
static void ILI9341_draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
