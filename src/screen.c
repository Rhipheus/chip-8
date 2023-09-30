#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"

int isRunning = 0;
int scale=10;

int initWindow(Chip8* chip8)
{
     if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Window* win = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       chip8->screen[0]*scale, 
                                       chip8->screen[1]*scale, 
                                       SDL_WINDOW_BORDERLESS);
    if(!win)
    {
        printf("error creating SDL window: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Renderer* renderer =SDL_CreateRenderer(win,-1,0);

    if(!renderer)
    {
        printf("error creating SDL renderer: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

int handleInput(Chip8* chip8)
{

}