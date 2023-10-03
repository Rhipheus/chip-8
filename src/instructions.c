#include "chip8.h"
#define SCREEN_SCALE 10
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

void OP_00E0(Chip8* chip8)
{
    //CLS
    for (unsigned int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++)
    {
        chip8->screen[i]=0;
    }
    
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
    unsigned int address = chip8->opcode & 0x0FFFu;
    chip8->pc = address;
}

void OP_2NNN(Chip8* chip8)
{
    //CALL NNN
    unsigned int address = chip8->opcode & 0x0FFFu;
    chip8->stack[chip8->sp]= chip8->pc;
    chip8->sp++;
    chip8->pc=address;
}

void OP_3xkk(Chip8* chip8)
{
    //Skip next instruction if Vx = kk.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int kk = chip8->opcode & 0x00FFu;

	if (chip8->registers[Vx] == kk)
	{
		chip8->pc += 2;
	}
}

void OP_4xkk(Chip8* chip8)
{
    //Skip next instruction if Vx != kk.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int kk = chip8->opcode & 0x00FFu;

	if (chip8->registers[Vx] != kk)
	{
		chip8->pc += 2;
	}
}

void OP_5xy0(Chip8* chip8)
{
    //Skip next instruction if Vx = Vy.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u;

	if (chip8->registers[Vx] = chip8->registers[Vy])
	{
		chip8->pc += 2;
	}
}

void OP_6xkk(Chip8* chip8)
{
    //Set Vx = kk.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int kk = chip8->opcode & 0x00FFu;

    chip8->registers[Vx] = kk;
}

void OP_7xkk(Chip8* chip8)
{
    //Set Vx = Vx + kk.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int kk = chip8->opcode & 0x00FFu; 

    chip8->registers[Vx] += kk;
}

void OP_8xy0(Chip8* chip8)
{
    //Set Vx = Vy.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    chip8->registers[Vx] = chip8->registers[Vy];
}

void OP_8xy1(Chip8* chip8)
{
    //Set Vx = Vx OR Vy.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    chip8->registers[Vx] |= chip8->registers[Vy];
}

void OP_8xy2(Chip8* chip8)
{
    //Set Vx = Vx AND Vy.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    chip8->registers[Vx] &= chip8->registers[Vy];
}

void OP_8xy3(Chip8* chip8)
{
    //Set Vx = Vx XOR Vy.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    chip8->registers[Vx] ^= chip8->registers[Vy];
}

void OP_8xy4(Chip8* chip8)
{
    //Set Vx = Vx + Vy, set VF = carry.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    unsigned int sum = chip8->registers[Vx] + chip8->registers[Vy];
    
    if (sum>255U)
    {
        chip8->registers[0xF] = 1;
    }
    else
    {
        chip8->registers[0xF] = 0;
    }
    chip8->registers[Vx] = sum & 0xFFu;
}

void OP_8xy5(Chip8* chip8)
{
    //Set Vx = Vx - Vy, set VF = NOT borrow.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u; 
    
    if (chip8->registers[Vx]>chip8->registers[Vy])
    {
        chip8->registers[0xF] = 1;
    }
    else
    {
        chip8->registers[0xF] = 0;
    }
    chip8->registers[Vx] -= chip8->registers[Vy];
}

void OP_8xy6(Chip8* chip8)
{
    //Set Vx = Vx SHR 1.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
    
    chip8->registers[0xF] = (chip8->registers[Vx] & 0x1u);
    chip8->registers[Vx] >>= 1;
}

void OP_8xy7(Chip8* chip8)
{
    //Set Vx = Vy - Vx, set VF = NOT borrow.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u; 
    
    if (chip8->registers[Vy]>chip8->registers[Vx])
    {
        chip8->registers[0xF] = 1;
    }
    else
    {
        chip8->registers[0xF] = 0;
    }
    chip8->registers[Vx] = chip8->registers[Vy]-chip8->registers[Vx];
}

void OP_8xyE(Chip8* chip8)
{
    //Set Vx = Vx SHL 1.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
    
    chip8->registers[0xF] = (chip8->registers[Vx] & 0x80u) >> 7u;
    chip8->registers[Vx] <<= 1;
}

void OP_9xy0(Chip8* chip8)
{
    //Skip next instruction if Vx != Vy.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00FFu) >> 4u;

	if (chip8->registers[Vx] != Vy)
	{
		chip8->pc += 2;
	}
}

void OP_Annn(Chip8* chip8)
{
    //Set I = nnn.
    unsigned int address = chip8->opcode & 0x0FFFu;
    chip8->index = address;
}

void OP_Bnnn(Chip8* chip8)
{
    //Jump to location nnn + V0.
    unsigned int address = chip8->opcode & 0x0FFFu;
    chip8->pc = chip8->registers[0]+address;
}

void OP_Cxkk(Chip8* chip8)
{
    //Set Vx = random byte AND kk.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int kk = chip8->opcode & 0x00FFu;

    chip8->registers[Vx] = (randNumGen() & kk);
}

void OP_Dxyn(Chip8* chip8)
{
    //Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int Vy = (chip8->opcode & 0x00F0u) >> 4u;
	unsigned int height = chip8->opcode & 0x000Fu;

	// Wrap if going beyond screen boundaries
	unsigned int xPos = chip8->registers[Vx] % SCREEN_WIDTH; //CHECK SCALE
	unsigned int yPos = chip8->registers[Vy] % SCREEN_HEIGHT; //CHECK SCALE

	chip8->registers[0xF] = 0;

	for (unsigned int row = 0; row < height; ++row)
	{
		unsigned int spriteByte = chip8->memory[chip8->index + row];

		for (unsigned int col = 0; col < 8; ++col)
		{
			unsigned int spritePixel = spriteByte & (0x80u >> col);
			unsigned int* screenPixel = &chip8->screen[(yPos + row) * SCREEN_WIDTH + (xPos + col)]; // CHECK WIDTH

			// Sprite pixel is on
			if (spritePixel)
			{
				// Screen pixel also on - collision
				if (*screenPixel == 0xFFFFFFFF)
				{
					chip8->registers[0xF] = 1;
				}

				// Effectively XOR with the sprite pixel
				*screenPixel ^= 0xFFFFFFFF;
			}
		}
	}
}

void OP_Ex9E(Chip8* chip8)
{
    //Skip next instruction if key with the value of Vx is pressed.
	unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;

	unsigned int key = chip8->registers[Vx];

	if (chip8->keypad[key])
	{
		chip8->pc += 2;
	}
}

void OP_ExA1(Chip8* chip8)
{
    //Skip next instruction if key with the value of Vx is not pressed.
	unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;

	unsigned int key = chip8->registers[Vx];

	if (!chip8->keypad[key])
	{
		chip8->pc += 2;
	}
}

void OP_Fx07(Chip8* chip8)
{
    //Set Vx = delay timer value.
	unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	chip8->registers[Vx] = chip8->delayTimer;
}

void OP_Fx0A(Chip8* chip8)
{
    //Wait for a key press, store the value of the key in Vx.
	unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;

    if (chip8->keypad[0])
	{
		chip8->registers[Vx] = 0;
	}
	else if (chip8->keypad[1])
	{
		chip8->registers[Vx] = 1;
	}
	else if (chip8->keypad[2])
	{
		chip8->registers[Vx] = 2;
	}
	else if (chip8->keypad[3])
	{
		chip8->registers[Vx] = 3;
	}
	else if (chip8->keypad[4])
	{
		chip8->registers[Vx] = 4;
	}
	else if (chip8->keypad[5])
	{
		chip8->registers[Vx] = 5;
	}
	else if (chip8->keypad[6])
	{
		chip8->registers[Vx] = 6;
	}
	else if (chip8->keypad[7])
	{
		chip8->registers[Vx] = 7;
	}
	else if (chip8->keypad[8])
	{
		chip8->registers[Vx] = 8;
	}
	else if (chip8->keypad[9])
	{
		chip8->registers[Vx] = 9;
	}
	else if (chip8->keypad[10])
	{
		chip8->registers[Vx] = 10;
	}
	else if (chip8->keypad[11])
	{
		chip8->registers[Vx] = 11;
	}
	else if (chip8->keypad[12])
	{
		chip8->registers[Vx] = 12;
	}
	else if (chip8->keypad[13])
	{
		chip8->registers[Vx] = 13;
	}
	else if (chip8->keypad[14])
	{
		chip8->registers[Vx] = 14;
	}
	else if (chip8->keypad[15])
	{
		chip8->registers[Vx] = 15;
	}
	else
	{
		chip8->pc -= 2;
	}
}

void OP_Fx15(Chip8* chip8)
{
    //Set delay timer = Vx.
	unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	chip8->delayTimer = chip8->registers[Vx];
}

void OP_Fx18(Chip8* chip8)
{
    //Set Vx = delay timer value.
	unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	chip8->soundTimer = chip8->registers[Vx];
}

void OP_Fx1E(Chip8* chip8)
{
    //Set I = I + Vx.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;

    chip8->index += chip8->registers[Vx];
}

void OP_Fx29(Chip8* chip8)
{
    //Set I = location of sprite for digit Vx.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
    unsigned int digit = chip8->registers[Vx];
    chip8->index = 0x50 + (5*digit); //FONTSE_START_ADDRESS HARDCODED!
}

void OP_Fx33(Chip8* chip8)
{
    //Store BCD representation of Vx in memory locations I, I+1, and I+2.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int value = chip8->registers[Vx];

	// Ones-place
	chip8->memory[chip8->index + 2] = value % 10;
	value /= 10;

	// Tens-place
	chip8->memory[chip8->index + 1] = value % 10;
	value /= 10;

	// Hundreds-place
	chip8->memory[chip8->index] = value % 10;
}

void OP_Fx55(Chip8* chip8)
{
    //Store registers V0 through Vx in memory starting at location I.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned int value = chip8->registers[Vx];

	for (unsigned int i = 0; i <= Vx; ++i)
	{
		chip8->memory[chip8->index + i] = chip8->registers[i];
	}
}

void OP_Fx65(Chip8* chip8)
{
    //Store registers V0 through Vx in memory starting at location I.
    unsigned int Vx = (chip8->opcode & 0x0F00u) >> 8u;

	for (unsigned int i = 0; i <= Vx; ++i)
	{
		chip8->registers[i] = chip8->memory[chip8->index + i];
	}
}