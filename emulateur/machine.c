#include "./include/machine.h"

void manageMachine()
{
    FILE* fichier;
    uint8_t valeur;
    fichier = fopen("./rom/5-quirks.ch8", "rb");
    struct t_processor* processor = newProcessor();
    u_int16_t i = 0;

    while (fread(&valeur, sizeof(uint8_t), 1, fichier))
    {
        writeRAM(processor->RAM, (512+i), valeur);
        i++;
    }
    processor->programCounter = 512;
    unsigned int test = 0;
    while(1)
    {
        SDL_Delay(2);
        fetchDecodeExecute(processor);
        if (test == 8)
        {
            Display_update(processor->display);
            decrementTimer(processor);
            test = 0;
        }
        test++;
    }
}