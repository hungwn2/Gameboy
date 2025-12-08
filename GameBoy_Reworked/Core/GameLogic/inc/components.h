/*
 * components.h
 *
 *  Created on: Nov 22, 2025
 *      Author: henryhungwy
 */

#pragma once


#include <math.h>
#include <stdio.h>


typedef struct{
	uint8_t imageWidth;
	uint8_t imageHeight;
	int16_t x;
	int16_t y;
	double dx;
	double dy;
	flag isAlive;
	flage direction;
};
