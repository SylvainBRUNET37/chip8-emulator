#include "processor.h"

int initProcessor(struct t_processor* processor)
{ 
    processor->RAM = newRAM();
    if ((processor->RAM) == NULL)
        return 1;

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