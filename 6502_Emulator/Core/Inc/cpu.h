/*
 * cpu.h
 *
 *  Created on: Nov 6, 2025
 *      Author: henryhungwy
 */

#ifndef INC_CPU_H_
#define INC_CPU_H_
#include <stdint.h>
#include <stdbool.h>

typedef enum{
	C_FLAG=(1<<0),
	Z_FLAG=(1<<1),
	I_FLAG=(1<<2),
	D_FLAG=(1<<3),
	B_FLAG=(1<<4),
	U_FLAG=(1<<5),
	V_FLAG=(1<<6),
	N_FLAG=(1<<7)
}cpu_flag_t;

typedef struct{
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t sp;
    uint16_t pc;
    uint8_t p;
    uint64_t cycles;
}cpu_t;


void cpu_reset(cpu_t *cpu);

void cpu_step(cpu_t *cpu);

void cpu_irq();

#endif /* INC_CPU_H_ */
