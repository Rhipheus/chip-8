#include "chip8.h"

void OP_00E0(Chip8* chip8)
{
    //CLS
}

void OP_00EE(Chip8* chip8)
{
    //RET
    chip8->sp--;
    chip8->pc = chip8->stack[chip8->sp];
}

void OP_1NNN(Chip8* chip8)
{
    //JP NNN
    unsigned short address = chip8->opcode & 0x0FFFu;
    chip8->pc = address;
}

void OP_2NNN(Chip8* chip8)
{
    //CALL NNN
    unsigned short address = chip8->opcode & 0x0FFFu;
    chip8->stack[chip8->sp]= chip8->pc;
    chip8->sp++;
    chip8->pc=address;
}

void OP_00E0(Chip8* chip8)
{
    //CLS
}