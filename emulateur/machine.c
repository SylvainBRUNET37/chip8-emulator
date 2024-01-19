#include "./include/machine.h"

void manageMachine()
{
    FILE* fichier;
    uint8_t valeur;
    fichier = fopen("./chip8-logo.ch8", "r");
    struct t_processor* processor = newProcessor();
    unsigned int i = 0;

    while (fread(&valeur, 1, sizeof(uint8_t), fichier))
    {
        writeRAM(processor->RAM, 512+i, valeur);
        printf("valeur de i : %d\n", i);
        printf("valeur en ram : %d\n", valeur);
        i++;
    }

    while(1)
    {
        sleep(0.2);
        //printf("valeur : %d\n", valeur);
        fetchDecodeExecute(processor);
        Display_update(processor->display);
        decrementTimer(processor);
    }
}