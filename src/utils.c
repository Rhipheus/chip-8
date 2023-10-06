#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"

int isRunning = 1;
int scale=10;

SDL_Window* win;
SDL_Renderer* renderer;
SDL_Texture* texture;

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
                            SDL_WINDOW_RESIZABLE);
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

int handleInput(Chip8* chip8)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_1:
                chip8->keypad[1]=1;
                printf("1");
                break;
            case SDLK_2:
                chip8->keypad[2]=1;
                printf("2");
                break;
            case SDLK_3:
                chip8->keypad[3]=1;
                printf("3");
                break;
            case SDLK_4:
                chip8->keypad[12]=1;
                printf("4");
                break;
            case SDLK_q:
                chip8->keypad[4]=1;
                printf("q");
                break;
            case SDLK_w:
                chip8->keypad[5]=1;
                printf("w");
                break;
            case SDLK_e:
                chip8->keypad[6]=1;
                printf("e");
                break;
            case SDLK_r:
                chip8->keypad[13]=1;
                printf("r");
                break;
            case SDLK_a:
                chip8->keypad[7]=1;
                printf("a");
                break;
            case SDLK_s:
                chip8->keypad[8]=1;
                printf("s");
                break;
            case SDLK_d:
                chip8->keypad[9]=1;
                printf("d");
                break;
            case SDLK_f:
                chip8->keypad[14]=1;
                printf("f");
                break;
            case SDLK_z:
                chip8->keypad[10]=1;
                printf("z");
                break;
            case SDLK_x:
                chip8->keypad[0]=1;
                printf("x");
                break;
            case SDLK_c:
                chip8->keypad[11]=1;
                printf("c");
                break;
            case SDLK_v:
                chip8->keypad[15]=1;
                printf("v");
                break;
        }
    }
    if(event.type == SDL_KEYUP)
    {
        printf("heré!");
        switch (event.key.keysym.sym)
        {
         case SDLK_1:
            chip8->keypad[1]=0;
            printf(" 1up");
            break;
    
        case SDLK_2:
            chip8->keypad[2]=0;
            printf(" 2up");
            break;
        case SDLK_3:
            chip8->keypad[3]=0;
            printf(" 3up");
            break;
        case SDLK_4:
            chip8->keypad[12]=0;
            printf(" 4up");
            break;
        case SDLK_q:
            chip8->keypad[4]=0;
            printf(" qup");
            break;
        case SDLK_w:
            chip8->keypad[5]=0;
            printf(" wup");
            break;
        case SDLK_e:
            chip8->keypad[6]=0;
            printf(" eup");
            break;
        case SDLK_r:
            chip8->keypad[13]=0;
            printf(" rup");
            break;
        case SDLK_a:
            chip8->keypad[7]=0;
            printf(" aup");
            break;
        case SDLK_s:
            chip8->keypad[8]=0;
            printf(" sup");
            break;
        case SDLK_d:
            chip8->keypad[9]=0;
            printf(" dup");
            break;
        case SDLK_f:
            chip8->keypad[14]=0;
            printf(" fup");
            break;
        case SDLK_z:
            chip8->keypad[10]=0;
            printf(" zup");
            break;
        case SDLK_x:
            chip8->keypad[0]=0;
            printf(" xup");
            break;
        case SDLK_c:
            chip8->keypad[11]=0;
            printf(" cup");
            break;
        case SDLK_v:
            chip8->keypad[15]=0;
            printf(" vup");
            break;
        }
    }
}
