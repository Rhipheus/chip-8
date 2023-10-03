#ifndef CHIP8_H
#define CHIP8_H

typedef struct chip8
{
unsigned int memory[4096];
unsigned int stack[16];
unsigned int registers[16];
unsigned int sp;
unsigned int pc;
unsigned int index;
unsigned int screen[64 * 32];
unsigned int opcode;
unsigned int keypad[16];
unsigned int delayTimer;
unsigned int soundTimer;
}Chip8;

void loadRom(Chip8* chip8,const char *file_name);
void loadFont(Chip8* chip8);
void loadInstructions(Chip8* chip);
void Cycle(Chip8* chip8);
unsigned int randNumGen();
#endif