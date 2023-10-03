#include "chip8.h"
#include "instructions.h"
#include <stdio.h>
#include <stdlib.h>


const unsigned int rom_start_add = 0x200;
const unsigned int font_start_add = 0x50;
const unsigned int fontset_size = 80;

unsigned char fontset[80] = // Hardcoded!
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void loadRom(Chip8* chip8,const char *file_name)
{
    printf("Loading rom file to memory...\n");
    FILE *file = fopen(file_name, "rb");

    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        int bufferSize = ftell(file);
        rewind(file);
        for (unsigned int i = rom_start_add; i <bufferSize+rom_start_add; i++)
        {
            chip8->memory[i]=getc(file);
        }
        
        fclose(file);
        printf("Loading rom file process done!\n");
    }
    else
    {
        printf("BAD FILE! Check rom file again.\n");
    }
}
void loadFont(Chip8* chip8)
{
    printf("Loading fontset to memory...\n");
    for (unsigned int i = 0; i < fontset_size; i++)
    {
        chip8->memory[font_start_add+i]=fontset[i];
    }
    printf("Loading fontset process done!\n");
}

void loadInstructions(Chip8* chip8)
{
    switch (chip8->opcode & 0xF000) {
        case 0x0000:
            switch (chip8->opcode) {
                case 0x00E0:
                    OP_00E0(chip8);
                    break;
                case 0x00EE:
                    OP_00EE(chip8);
                    break;
            }

            break;
        case 0x1000:
            OP_1NNN(chip8);
            break;
        case 0x2000:
            OP_2NNN(chip8);
            break;
        case 0x3000:
            OP_3xkk(chip8);
            break;
        case 0x4000:
            OP_4xkk(chip8);
            break;
        case 0x5000:
            OP_5xy0(chip8);
            break;
        case 0x6000:
            OP_6xkk(chip8);
            break;
        case 0x7000:
            OP_7xkk(chip8);
            break;
        case 0x8000:
            switch (chip8->opcode & 0xF) {
                case 0x0:
                    OP_8xy0(chip8);
                    break;
                case 0x1:
                    OP_8xy1(chip8);
                    break;
                case 0x2:
                    OP_8xy2(chip8);
                    break;
                case 0x3:
                    OP_8xy3(chip8);
                    break;
                case 0x4:
                    OP_8xy4(chip8);
                    break;
                case 0x5:
                    OP_8xy5(chip8);
                    break;
                case 0x6:
                    OP_8xy6(chip8);
                    break;
                case 0x7:
                    OP_8xy7(chip8);
                    break;
                case 0xE:
                    OP_8xyE(chip8);
                    break;
            }

            break;
        case 0x9000:
            OP_9xy0(chip8);
            break;
        case 0xA000:
            OP_Annn(chip8);
            break;
        case 0xB000:
            OP_Bnnn(chip8);
            break;
        case 0xC000:
            OP_Cxkk(chip8);
            break;
        case 0xD000:
            OP_Dxyn(chip8);
            break;
        case 0xE000:
            switch (chip8->opcode & 0xFF) {
                case 0x9E:
                    OP_Ex9E(chip8);
                    break;
                case 0xA1:
                    OP_ExA1(chip8);
                    break;
            }

            break;
        case 0xF000:
            switch (chip8->opcode & 0xFF) {
                case 0x07:
                    OP_Fx07(chip8);
                    break;
                case 0x0A:
                    OP_Fx0A(chip8);
                    break;
                case 0x15:
                    OP_Fx15(chip8);
                    break;
                case 0x18:
                    OP_Fx18(chip8);
                    break;
                case 0x1E:
                    OP_Fx1E(chip8);
                    break;
                case 0x29:
                    OP_Fx29(chip8);
                    break;
                case 0x33:
                    OP_Fx33(chip8);
                    break;
                case 0x55:
                    OP_Fx55(chip8);
                    break;
                case 0x65:
                    OP_Fx65(chip8);
                    break;
            }

        break;
    }
}   

void Cycle(Chip8* chip8)
{
    chip8->opcode = (chip8->memory[chip8->pc] << 8u) | chip8->memory[chip8->pc + 1];
    chip8->pc+=2;

    loadInstructions(chip8);

    if (chip8->delayTimer > 0)
	{
		--(chip8->delayTimer);
	}

	// Decrement the sound timer if it's been set
	if (chip8->soundTimer > 0)
	{
		--(chip8->soundTimer);
	}
}

unsigned int randNumGen()
{
    //Random number between 0-256;

    unsigned int randomNumber = rand() % 256;
    return randomNumber;
}