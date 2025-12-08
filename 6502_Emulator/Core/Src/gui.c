#include "uart.h"
#include "gpio.h"
#include "cpu.h"
#include <stdbool.h>

static char to_hex_char(uint8_t nibble){
	  nibble &= 0x0F;
	    if (nibble < 10) {
	        return nibble + '0';
	    }
	    return (nibble - 10) + 'A';
}

static void term_print_hex(uint32_t val, uint8_t digits) {
    // Print from the most significant digit down
    for (int i = (digits - 1) * 4; i >= 0; i -= 4) {
        uart_write_byte(to_hex_char((val >> i)));
    }
}

static void term_print_uint(uint32_t n){
	if (n==0){
		uart_write_byte('0');
		return;
	}
	if (n>=0){
		term_print_uint(n/10);
	}
    uart_write_byte((n % 10) + '0');

}

void term_init(void){
    uart_write_string("\r\n--- 6502 Emulator Started ---\r\n");
}


void term_update_dashboard(cpu_t* cpu) {
    // Print PC
    uart_write_string("PC:$"); term_print_hex(cpu->pc, 4);

    // Print SP
    uart_write_string(" SP:$"); term_print_hex(cpu->sp, 2);

    // Print A, X, Y
    uart_write_string(" A:$"); term_print_hex(cpu->a, 2);
    uart_write_string(" X:$"); term_print_hex(cpu->x, 2);
    uart_write_string(" Y:$"); term_print_hex(cpu->y, 2);

    // Print Flags
    uart_write_string(" P:[");
    uart_write_byte(cpu->p & N_FLAG ? 'N' : '.');
    uart_write_byte(cpu->p & V_FLAG ? 'V' : '.');
    uart_write_byte(cpu->p & U_FLAG ? 'U' : '.'); // U-flag
    uart_write_byte(cpu->p & B_FLAG ? 'B' : '.');
    uart_write_byte(cpu->p & D_FLAG ? 'D' : '.');
    uart_write_byte(cpu->p & I_FLAG ? 'I' : '.');
    uart_write_byte(cpu->p & Z_FLAG ? 'Z' : '.');
    uart_write_byte(cpu->p & C_FLAG ? 'C' : '.');
    uart_write_string("] ");

    // Print Cycles
    uart_write_string("CYC:"); term_print_uint(cpu->cycles);

    // Print a newline to scroll
    uart_write_string("\r\n");
}
