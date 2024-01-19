#include "./include/machine.h"

void manageMachine()
{
    FILE* fichier;
    uint8_t test;
    fichier = fopen("./chip8-logo.ch8", "r");
    struct t_processor* processor = newProcessor();

    while(1)
    {
        fread(&test, 1, sizeof(uint8_t), fichier);
        //printf("test : %d\n", test);
        fetchDecodeExecute(processor);
    }
}