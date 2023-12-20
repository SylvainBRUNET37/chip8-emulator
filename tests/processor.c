#include "processor.h"

int initProcessor(struct t_processor* processor)
{
    processor->RAM = newRAM();
    if ((processor->RAM) == NULL)
        return 1;
    return 0;
}

void destroyProcessor(struct t_processor* processor)
{
    if (processor != NULL)
        free(processor->RAM);
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