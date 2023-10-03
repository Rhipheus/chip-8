#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "utils.h"

Chip8 chip8;
Chip8* chip8_ptr = &chip8;


int main(int argv, char** args)
{
    chip8_ptr->pc=0x200;
    loadRom(chip8_ptr,"test/slipperyslope.ch8");
    loadFont(chip8_ptr);
    loadInstructions(chip8_ptr);
    initWindow(chip8_ptr,64,32);
}