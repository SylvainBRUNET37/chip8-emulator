/**
 * \file  processor.c
 * \brief Contient les définitions des fonctions liées à la structure \ref t_processor 
 */

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
    
    // Initialise le processeur
    resetProcessor(processor);
    return processor;
}

void deleteProcessor(struct t_processor* processor)
{
    // Reinitialise les valeurs des variables de processeur à 0 et libère la mémoire de la structure
    if (processor != NULL)
    {
        resetProcessor(processor);
        free(processor);
    }
}

void decrementTimer(struct t_processor* processor)
{
    // Décrémente les timers si ils ne sont pas à 0
    if (processor->delayTimerRegister != 0)
        processor->delayTimerRegister--;
    if (processor->soundTimerRegister != 0)
        processor->soundTimerRegister--;
}