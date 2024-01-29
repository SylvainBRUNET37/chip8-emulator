#include "./include/machine.h"
#include <SDL2/SDL.h>

void manageMachine()
{
    struct t_processor* processor = newProcessor();
    loadRepresentativeSprite(processor);
    loadRom();
    processor->programCounter = 512;
    
    unsigned int test = 0;
    while(1)
    {
        SDL_Delay(2);
        fetchDecodeExecute(processor);
        if (test == 1)
        {
            Display_update(processor->display);
            decrementTimer(processor);
            test = 0;
        }
        test++;
    }
}

void fetchDecodeExecute(struct t_processor* processor)
{
    uint16_t instruction = readRAM(processor->RAM, processor->programCounter);
    instruction = instruction << 8;
    instruction += readRAM(processor->RAM, processor->programCounter+1);
    processor->programCounter += 2;

    //printf("Instruction : %x\n", instruction);
    
    if ((instruction & 0xF000) == 0x0000)
    {
        if ((instruction & 0xFFFF) == 0x00E0)
        {
            CLS_00E0(processor);
        }
        else if ((instruction & 0xFFFF) == 0x00EE)
        {
            RET_00EE(processor);
        }
    }
    else if ((instruction & 0xF000) == 0x1000)
    {
        JP_1nnn(processor, instruction & 0x0FFF);
    }
    else if ((instruction & 0xF000) == 0x2000)
    {
        CALL_2nnn(processor, instruction  & 0x0FFF);
    }
    else if ((instruction & 0xF000) == 0x3000)
    {
        SE_3xkk(processor, (instruction & 0x0F00) >> 8, (uint8_t)(instruction & 0x00FF));
    }
    else if ((instruction & 0xF000) == 0x4000)
    {
        SNE_4xkk(processor, (instruction & 0x0F00) >> 8, (uint8_t)(instruction & 0x00FF));
    }
    else if ((instruction & 0xF00F) == 0x5000)
    {
        SE_5xy0(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
    }
    else if ((instruction & 0xF000) == 0x6000)
    {
        LD_6xkk(processor, (instruction & 0x0F00) >> 8, (u_int8_t)(instruction & 0x00FF));
    }
    else if ((instruction & 0xF000) == 0x7000)
    {
        ADD_7xkk(processor, (instruction & 0x0F00) >> 8, (uint8_t)(instruction & 0x00FF));
    }
    else if ((instruction & 0xF000) == 0x8000)
    {
        if ((instruction & 0xF00F) == 0x8000)
        {
            LD_8xy0(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
        else if ((instruction & 0xF00F )== 0x8001)
        {
            OR_8xy1(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
        else if ((instruction & 0xF00F) == 0x8002)
        {
            AND_8xy2(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
        else if ((instruction & 0xF00F) == 0x8003)
        {
            XOR_8xy3(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
        else if ((instruction & 0xF00F) == 0x8004)
        {
            ADD_8xy4(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
        else if ((instruction & 0xF00F) == 0x8005)
        {
            SUB_8xy5(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
        else if ((instruction & 0xF00F) == 0x8006)
        {
            SHR_8xy6(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }   
        else if ((instruction & 0xF00F) == 0x8007)
        {
            SUBN_8xy7(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
        else if ((instruction & 0xF00F) == 0x800E)
        {
            SHL_8xyE(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
    }
    else if ((instruction & 0xF00F) == 0x9000)
    {
        SNE_9xy0(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
    }
    else if ((instruction & 0xF000) == 0xA000)
    {
        LD_Annn(processor, instruction & 0x0FFF);
    }
    else if ((instruction  & 0xF000) == 0xB000)
    {
        JP_Bnnn(processor, instruction  & 0x0FFF);
    }   
    else if ((instruction  & 0xF000) == 0xC000)
    {
        RND_Cxkk(processor, (instruction & 0x0F00) >> 8, (uint8_t)(instruction & 0x00FF));
    }
    else if ((instruction & 0xF000) == 0xD000)
    {
        DRW_Dxyn(processor, (instruction  & 0x0F00) >> 8, (instruction & 0x00F0) >> 4, instruction & 0x000F);
    }
    else if ((instruction & 0xF000) == 0xE000)
    {
        if ((instruction & 0xF0FF) == 0xE09E)
        {
            SKP_Ex9E(processor, (instruction & 0x0F00) >> 8);
        }
        else if ((instruction & 0xF0FF) == 0xE0A1)
        {
            SKNP_ExA1(processor, (instruction & 0x0F00) >> 8);
        }
    }
    else if ((instruction & 0xF000) == 0xF000)
    {
        if ((instruction & 0xF0FF) == 0xF007)
        {
            LD_Fx07(processor, (instruction & 0x0F00) >> 8);
        }
        else if ((instruction & 0xF0FF) == 0xF00A)
        {
            LD_Fx0A(processor, (instruction & 0x0F00) >> 8);
        }
        else if ((instruction & 0xF0FF) == 0xF015)
        {
            LD_Fx15(processor, (instruction & 0x0F00 ) >> 8);
        }
        else if ((instruction & 0xF0FF) == 0xF018)
        {
            LD_Fx18(processor, (instruction & 0x0F00) >> 8);
        }
        else if ((instruction & 0xF0FF) == 0xF01E)
        {
            ADD_Fx1E(processor, (instruction & 0x0F00) >> 8);
        }
        else if ((instruction & 0xF0FF )== 0xF029)
        {
            LD_Fx29(processor, (instruction & 0x0F00) >> 8);
        }
        else if ((instruction & 0xF0FF) == 0xF033)
        {
            LD_Fx33(processor, (instruction & 0x0F00) >> 8);
        }
        else if ((instruction & 0xF0FF) == 0xF055)
        {
            LD_Fx55(processor, (instruction & 0x0F00) >> 8);
        }
        else if ((instruction & 0xF0FF) == 0xF065)
        {
            LD_Fx65(processor, (instruction & 0x0F00) >> 8);
        }
    }
}

void loadRepresentativeSprite(struct t_processor* processor)
{
    // Déclaration d'un tableau contenant les sprites représentatifs des chiffres hexadécimaux
    uint8_t representativeSprite[NB_REPRESENTATIVE_SPRITE] = 
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
    for (uint8_t i = 0 ; i < NB_REPRESENTATIVE_SPRITE ; i++)
        writeRAM(processor->RAM, i, representativeSprite[i]);
}

void loadRom(struct t_processor* processor)
{
    FILE* fichier;
    uint8_t valeur;
    u_int16_t i = 0;
    fichier = fopen("./rom/Pong (1 player).ch8", "rb");
    

    while (fread(&valeur, sizeof(uint8_t), 1, fichier))
    {
        writeRAM(processor->RAM, (512+i), valeur);
        i++;
    }
}