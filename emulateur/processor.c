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