#ifndef CHIP8_H
#define CHIP8_H

typedef struct chip8
{
unsigned short memory[4096];
unsigned char stack[16];
unsigned char registers[16];
unsigned char sp;
unsigned short pc;
unsigned char index;
unsigned short screen[64 * 32];
unsigned char opcode;
}Chip8;

void loadRom(Chip8* chip8,const char *file_name);
void loadFont(Chip8* chip8);
void initSystem(Chip8* chip8);
unsigned short randNumGen();
#endif