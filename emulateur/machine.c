#include "./include/machine.h"

void manageMachine()
{
    FILE* fichier;
    uint8_t valeur;
    fichier = fopen("./chip8-logo.ch8", "rb");
    struct t_processor* processor = newProcessor();
    unsigned int i = 0;

    while (fread(&valeur, sizeof(uint8_t), 1, fichier))
    {
        writeRAM(processor->RAM, 512+i, valeur);
        //printf("valeur de i : %d\n", i);
        //printf("valeur en ram : %d\n", readRAM(processor->RAM, 512+i));
        i++;
    }
    processor->programCounter = 512;

    while(1)
    {
        sleep(1);
        //printf("valeur : %d\n", valeur);
        fetchDecodeExecute(processor);
        Display_update(processor->display);
        decrementTimer(processor);
    }
}