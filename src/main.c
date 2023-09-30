#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"

Chip8 chip8;
Chip8* chip8_ptr = &chip8;


int main(int argv, char** args)
{

    loadRom(chip8_ptr,"test/slipperyslope.ch8");
   
}