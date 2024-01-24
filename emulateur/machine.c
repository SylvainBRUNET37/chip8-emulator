#include "./include/machine.h"

void manageMachine()
{
    FILE* fichier;
    uint8_t valeur;
    fichier = fopen("./rom/5-quirks.ch8", "rb");
    struct t_processor* processor = newProcessor();
    unsigned int i = 0;

    while (fread(&valeur, sizeof(uint8_t), 1, fichier))
    {
        writeRAM(processor->RAM, (uint8_t)(512+i), valeur);
        i++;
    }
    processor->programCounter = 512;

    while(1)
    {
        //usleep(50000);
        fetchDecodeExecute(processor);
        Display_update(processor->display);
        decrementTimer(processor);
    }
}