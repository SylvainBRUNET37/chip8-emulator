#include "./include/instructions.h"

int initProcessor(struct t_processor* processor)
{ 
    processor->RAM = newRAM();
    if ((processor->RAM) == NULL)
        return 1;

    processor->display = malloc(sizeof(struct Display));
    processor->speaker = malloc(sizeof(struct Speaker));
    processor->keyboard = malloc(sizeof(struct Keyboard));

    Display_init(processor->display, 10);
    Speaker_init(processor->speaker);
    Keyboard_init(processor->keyboard);

    unsigned int i = 0;
    for (i = 0 ; i < nbGeneralRegister ; i++)
        processor->generalRegister[i] = 0;
    for (i = 0 ; i < nbStackElement ; i++)
        processor->stack[i] = 0;
    
    processor->delayTimerRegister = 0;
    processor->soundTimerRegister = 0;
    processor->programCounter = 0;
    processor->IRegister = 0;
    processor->stackPointer = 0;

    return 0;
}

void destroyProcessor(struct t_processor* processor)
{
    if (processor != NULL)
    {
        Display_destroy(processor->display);
        free(processor->display);
        
        Speaker_destroy(processor->speaker);
        free(processor->speaker);
        
        Keyboard_destroy(processor->keyboard);
        free(processor->keyboard);

        destroyRAM(processor->RAM);
        free(processor->RAM);

        unsigned int i = 0;
        for (i = 0 ; i < nbGeneralRegister ; i ++)
            processor->generalRegister[i] = 0;
        for (i = 0 ; i < nbStackElement ; i ++)
            processor->stack[i] = 0;

        processor->delayTimerRegister = 0;
        processor->soundTimerRegister = 0;
        processor->programCounter = 0;
        processor->IRegister = 0;
        processor->stackPointer = 0;
    }
}

struct t_processor* newProcessor(void)
{
    struct t_processor* processor = malloc(sizeof(struct t_processor));
    if (processor == NULL)
        return NULL;
    if (initProcessor(processor) == 1)
        return NULL;
    return processor;
}

void deleteProcessor(struct t_processor* processor)
{
    if (processor != NULL)
    {
        destroyProcessor(processor);
        free(processor);
    }
}

void decrementTimer(struct t_processor* processor)
{
    if (processor->delayTimerRegister != 0)
        processor->delayTimerRegister--;
    if (processor->soundTimerRegister != 0)
        processor->soundTimerRegister--;
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
            SHR_8xy6(processor, (instruction & 0x0F00) >> 8);
        }   
        else if ((instruction & 0xF00F) == 0x8007)
        {
            SUBN_8xy7(processor, (instruction & 0x0F00) >> 8, (instruction & 0x00F0) >> 4);
        }
        else if ((instruction & 0xF00F) == 0x800E)
        {
            SHL_8xyE(processor, (instruction & 0x0F00) >> 8);
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