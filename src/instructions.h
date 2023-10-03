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
void OP_8xyE(Chip8* chip8);
void OP_9xy0(Chip8* chip8);
void OP_Annn(Chip8* chip8);
void OP_Bnnn(Chip8* chip8);
void OP_Cxkk(Chip8* chip8);
void OP_Dxyn(Chip8* chip8);
void OP_Ex9E(Chip8* chip8);
void OP_ExA1(Chip8* chip8);
void OP_Fx07(Chip8* chip8);
void OP_Fx0A(Chip8* chip8);
void OP_Fx15(Chip8* chip8);
void OP_Fx18(Chip8* chip8);
void OP_Fx1E(Chip8* chip8);
void OP_Fx29(Chip8* chip8);
void OP_Fx33(Chip8* chip8);
void OP_Fx55(Chip8* chip8);
void OP_Fx65(Chip8* chip8);
#endif