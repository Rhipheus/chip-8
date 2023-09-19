#include "chip8.h"
#include <stdio.h>

const unsigned short rom_start_add = 0x200;
const unsigned short font_start_add = 0x50;
const unsigned short fontset_size = 80;

unsigned char fontset[80] = // Hardcoded!
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void loadRom(Chip8* chip8,const char *file_name)
{
    printf("Loading rom file to memory...\n");
    FILE *file = fopen(file_name, "rb");

    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        int bufferSize = ftell(file);
        rewind(file);
        for (unsigned short i = rom_start_add; i <bufferSize+rom_start_add; i++)
        {
            chip8->memory[i]=getc(file);
        }
        
        fclose(file);
        printf("Loading rom file process done!\n");
    }
    else
    {
        printf("BAD FILE! Check rom file again.\n");
    }
}
void loadFont(Chip8* chip8)
{
    printf("Loading fontset to memory...\n");
    for (unsigned short i = 0; i < fontset_size; i++)
    {
        chip8->memory[font_start_add+i]=fontset[i];
    }
    printf("Loading fontset process done!\n");
}

void initSystem(Chip8* chip8)
{
    printf("Initializing system...\n");
    chip8->pc=rom_start_add;
}