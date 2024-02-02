#include "./include/ram.h"

int initRAM(struct t_RAM* RAM)
{
    // Alloue les 4096 emplacements de 8 bits de la RAM
    RAM->ram = malloc(4096*sizeof(uint8_t));
    if (RAM->ram == NULL)
        return 1;
    return 0;
}

void destroyRAM(struct t_RAM* RAM)
{
    // Libère la mémoire de la ram
    if (RAM != NULL)
        free(RAM->ram);
}

struct t_RAM* newRAM(void)
{
    // Alloue la structure t_RAM et l'initialise
    struct t_RAM* RAM = malloc(sizeof(struct t_RAM));
    if (RAM == NULL)
        return NULL;
    if (initRAM(RAM) == 1)
        return NULL;
    return RAM;
}

void deleteRAM(struct t_RAM* RAM)
{
    // Libère la mémoire de la structure t_RAM
    if (RAM != NULL)
    {
        destroyRAM(RAM);
        free(RAM);
    }
}

int writeRAM(struct t_RAM* RAM, uint16_t adr, uint8_t val)
{
    if (RAM == NULL)
        return 1;
    RAM->ram[adr] = val;
    return 0;
}

uint8_t readRAM(struct t_RAM* RAM, uint16_t adr)
{
    return RAM->ram[adr];
}
