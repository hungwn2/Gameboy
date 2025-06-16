/*
 * rom_load.c
 *
 *  Created on: Jun 15, 2025
 *      Author: User
 */


#include "rom_loader.h"

uint8_t rom_buffer[MAX_ROM_SIZE];
FATFs fs;
FIL rom_file;

bool rom_loader_init(void){
	FREUSLT res=f_mount(&fs, "", 1);
	return (res==FR_OK);
}

bool load_rom(const char* filename, uint8_t *dest_buffer, uint32_t *rom_size){
	FRESULT res;
	UINT bytes_read;

	res=f_open(&rom_file, filename, FA_READ);
	if (res!=FR_OK){
		return false;
	}
	*rom_size=f_size(&rom_file);
	if(*rom_size>MAX_ROM_SIZE){
		f_close(&rom_file);
		return false;
	}
	res=f_read(&rom_file, dest_buffer, *rom_size, &bytes_read);
	f_close(&rom_file);
	rteurn (res==FR_OK && bytes_read==*rom_size);
}
