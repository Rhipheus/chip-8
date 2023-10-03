#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"

int isRunning = 1;
int scale=10;

SDL_Window* win;
SDL_Renderer* renderer;
SDL_Texture* texture;

unsigned int keyboard[16] = { 2,3,4,5,
                                16,17,18,19,
                                30,31,32,33,
                                44,45,46,47};

int initWindow(Chip8* chip8,int textureWidth,int textureHeight)
{
     if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    win = SDL_CreateWindow("GAME",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            64*scale, 
                            32*scale, 
                            SDL_WINDOW_BORDERLESS);
    if(!win)
    {
        printf("error creating SDL window: %s\n", SDL_GetError());
        return 0;
    }

    renderer =SDL_CreateRenderer(win,-1,0);
    if(!renderer)
    {
        printf("error creating SDL renderer: %s\n", SDL_GetError());
        return 0;
    }
    texture = SDL_CreateTexture(
			renderer, 
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_STREAMING, 
            textureWidth, 
            textureHeight);
    return 1;
}

void Update(void const* buffer, int pitch)
	{
		SDL_UpdateTexture(texture, NULL, buffer, pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

void destroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int findIndex(unsigned int arr[], int key)
{
     
    int arrLen = 16;
    int index = -1;
     
    for (int i = 0; i < arrLen; i++) {
        if (arr[i] == key) {
            index = i;
            break;
        }
    }
     
    if (index > -1) {
        return index;
    } else {
        printf("%d is not present in this array.\n", key);
    }
}

int handleInput(Chip8* chip8)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = 0;
        destroyWindow();
        break;
    
    case SDL_KEYDOWN:
        {
        int downindex = findIndex(keyboard,event.key.keysym.scancode);
        chip8->keypad[downindex]=1;
        if (event.key.keysym.scancode == 1)
        {
            isRunning = 0;
            destroyWindow();
        }
        }
    case SDL_KEYUP:
    {
        int upindex = findIndex(keyboard,event.key.keysym.scancode);
        chip8->keypad[upindex]=0;
    }
    default:
        break;
    }
}