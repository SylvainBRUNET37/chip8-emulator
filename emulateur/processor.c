#include "./include/processor.h"

void resetProcessor(struct t_processor* processor)
{ 
    if (processor != NULL)
    {
        unsigned int i = 0;
        // Initialise les registres générals et la pile
        for (i = 0 ; i < nbGeneralRegister ; i++)
            processor->generalRegister[i] = 0;
        for (i = 0 ; i < nbStackElement ; i++)
            processor->stack[i] = 0;
        
        // Initialise le reste
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
    resetProcessor(processor);
    return processor;
}

void deleteProcessor(struct t_processor* processor)
{
    if (processor != NULL)
    {
        resetProcessor(processor);
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