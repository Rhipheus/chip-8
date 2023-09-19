#include "chip8.h"
#include <stdio.h>

unsigned short memory[4096];
unsigned char stack[16];
unsigned char egisters[16];
unsigned char sp;
unsigned char pc;
unsigned char ind;
unsigned short screen[64 * 32];
unsigned char opcode;

void loadRom(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        int bufferSize = ftell(file);
        fclose(file);

    }
    else
    {
        printf("BAD FILE! Check rom file again.");
    }
}

/*
void OP_0NNN()
{
}

void OP_00E0()
{
    // CLS
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}

void OP_00E0()
{
}*/