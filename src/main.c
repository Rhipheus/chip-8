#include "chip8.h"

Chip8* chip8;


int main()
{
    loadFont(&chip8);
    //loadRom(chip8,"src/slipperyslope.ch8");
    return 0;
}