#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"

Chip8 chip8;
Chip8* chip8_ptr = &chip8;


int main(int argv, char** args)
{
    //loadFont(&chip8);
    loadRom(chip8_ptr,"test/slipperyslope.ch8");

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);
    while (1)
        ;
    return 0;
}