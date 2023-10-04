#ifndef UTILS_H
#define UTILS_H

#include "chip8.h"

int initWindow(Chip8* chip8,int textureWidth,int textureHeight);
void Update(void const* buffer, int pitch);
void destroyWindow();
void handleInput(Chip8* chip8);

#endif