#ifndef GUI_H
#define GUI_H

#include "cpu.h"
#include <stdint.h>
void term_init(void);

void term_update_dashboard(cpu_t* cpu);

#endif
