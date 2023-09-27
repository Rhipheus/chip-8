#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8.h"

void OP_00E0(Chip8* chip8);
void OP_00EE(Chip8* chip8);
void OP_1NNN(Chip8* chip8);
void OP_2NNN(Chip8* chip8);
void OP_3xkk(Chip8* chip8);
void OP_4xkk(Chip8* chip8);
void OP_5xy0(Chip8* chip8);
void OP_6xkk(Chip8* chip8);
void OP_7xkk(Chip8* chip8);
void OP_8xy0(Chip8* chip8);
void OP_8xy1(Chip8* chip8);
void OP_8xy2(Chip8* chip8);
void OP_8xy3(Chip8* chip8);
void OP_8xy4(Chip8* chip8);
void OP_8xy5(Chip8* chip8);
void OP_8xy6(Chip8* chip8);
void OP_8xy7(Chip8* chip8);
void OP_8xy8(Chip8* chip8);
void OP_9xy0(Chip8* chip8);
void OP_Annn(Chip8* chip8);
void OP_Bnnn(Chip8* chip8);
void OP_Cxkk(Chip8* chip8);

#endif