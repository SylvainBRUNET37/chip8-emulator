#include "./include/instructions.h"

int initProcessor(struct t_processor* processor)
{ 
    processor->RAM = newRAM();
    if ((processor->RAM) == NULL)
        return 1;

    Display_init(processor->display, 10);
    Speaker_init(processor->speaker);
    Keyboard_init(processor->keyboard);

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

    return 0;
}

void destroyProcessor(struct t_processor* processor)
{
    if (processor != NULL)
    {
        Display_destroy(processor->display);
        Speaker_destroy(processor->speaker);
        Keyboard_destroy(processor->keyboard);
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

void fetchDecodeExecute(struct t_processor* processor)
{
    fetch(processor);
    decode(processor);
}

void fetch(struct t_processor* processor)
{
    processor->IRegister = processor->RAM->ram[processor->programCounter];
    processor->IRegister << 8;
    processor->IRegister += processor->RAM->ram[processor->programCounter];
    processor->programCounter += 2;
}

void decode(struct t_processor* processor)
{
    if (processor->IRegister & 0xF000 == 0x0000)
    {
        if (processor->IRegister & 0x000F == 0x0000)
        {
            CLS_00E0(processor);
        }
        else if (processor->IRegister & 0x000F == 0x000E)
        {
            
        }
    }
    else if (processor->IRegister & 0xF000 == 1)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 2)
    {

    }
    else if (processor->IRegister & 0xF000 == 3)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 4)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 5)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 6)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 7)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 8)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 9)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 10)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 11)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 12)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 13)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 14)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 15)
    {
        
    }
    else if (processor->IRegister & 0xF000 == 16)
    {
        
    }
}
