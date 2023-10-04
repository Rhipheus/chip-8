#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "chip8.h"
#include "utils.h"
#include<windows.h>

Chip8 chip8;
Chip8* chip8_ptr = &chip8;
extern int isRunning;

int main(int argv, char** args)
{
    chip8_ptr->pc=0x200;
    loadRom(chip8_ptr,"test/chipquarium.ch8");
    loadFont(chip8_ptr);
    initWindow(chip8_ptr,64,32);
    
    while (isRunning)
    {
        Sleep(1);
              
        Cycle(chip8_ptr);
            
        Update(chip8_ptr->screen,sizeof(chip8_ptr->screen[0])*64);
            
        handleInput(chip8_ptr);
        
    }
    
    
}