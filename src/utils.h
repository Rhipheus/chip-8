#ifndef UTILS_H
#define UTILS_H

#include "chip8.h"

int initWindow(Chip8* chip8);
void destroyWindow();
int findIndex(unsigned short arr[], int key);
void handleInput(Chip8* chip8);

#endif