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

void OP_3xkk(Chip8* chip8)
{
    //Skip next instruction if Vx = kk.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short kk = chip8->opcode & 0x00FFu;

	if (chip8->registers[Vx] == kk)
	{
		chip8->pc += 2;
	}
}

void OP_4xkk(Chip8* chip8)
{
    //Skip next instruction if Vx != kk.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short kk = chip8->opcode & 0x00FFu;

	if (chip8->registers[Vx] != kk)
	{
		chip8->pc += 2;
	}
}

void OP_5xy0(Chip8* chip8)
{
    //Skip next instruction if Vx = Vy.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u;

	if (chip8->registers[Vx] = chip8->registers[Vy])
	{
		chip8->pc += 2;
	}
}

void OP_6xkk(Chip8* chip8)
{
    //Set Vx = kk.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short kk = chip8->opcode & 0x00FFu;

    chip8->registers[Vx] = kk;
}

void OP_7xkk(Chip8* chip8)
{
    //Set Vx = Vx + kk.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short kk = chip8->opcode & 0x00FFu; 

    chip8->registers[Vx] += kk;
}

void OP_8xy0(Chip8* chip8)
{
    //Set Vx = Vy.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    chip8->registers[Vx] = chip8->registers[Vy];
}

void OP_8xy1(Chip8* chip8)
{
    //Set Vx = Vx OR Vy.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    chip8->registers[Vx] |= chip8->registers[Vy];
}

void OP_8xy2(Chip8* chip8)
{
    //Set Vx = Vx AND Vy.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    chip8->registers[Vx] &= chip8->registers[Vy];
}

void OP_8xy3(Chip8* chip8)
{
    //Set Vx = Vx XOR Vy.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u; 

    chip8->registers[Vx] ^= chip8->registers[Vy];
}

void OP_8xy4(Chip8* chip8)
{
    //Set Vx = Vx + Vy, set VF = carry.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u; 

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
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u; 
    
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
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
    
    chip8->registers[0xF] = (chip8->registers[Vx] & 0x1u);
    chip8->registers[Vx] >>= 1;
}

void OP_8xy7(Chip8* chip8)
{
    //Set Vx = Vy - Vx, set VF = NOT borrow.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u; 
    
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

void OP_8xy8(Chip8* chip8)
{
    //Set Vx = Vx SHL 1.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
    
    chip8->registers[0xF] = (chip8->registers[Vx] & 0x80u) >> 7u;
    chip8->registers[Vx] <<= 1;
}

void OP_9xy0(Chip8* chip8)
{
    //Skip next instruction if Vx != Vy.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short Vy = (chip8->opcode & 0x00FFu) >> 4u;

	if (chip8->registers[Vx] != Vy)
	{
		chip8->pc += 2;
	}
}

void OP_Annn(Chip8* chip8)
{
    //Set I = nnn.
    unsigned short address = chip8->opcode & 0x0FFFu;
    chip8->index = address;
}

void OP_Bnnn(Chip8* chip8)
{
    //Jump to location nnn + V0.
    unsigned short address = chip8->opcode & 0x0FFFu;
    chip8->pc = chip8->registers[0]+address;
}

void OP_Cxkk(Chip8* chip8)
{
    //Set Vx = random byte AND kk.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
	unsigned short kk = chip8->opcode & 0x00FFu;

    chip8->registers[Vx] = (randNumGen() & kk);
}

void OP_Fx1E(Chip8* chip8)
{
    //Set I = I + Vx.
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;

    chip8->index += chip8->registers[Vx];
}