#include "./include/machine.h"
#include <SDL2/SDL.h>

// Déclaration d'un tableau contenant les sprites représentatifs des chiffres hexadécimals
uint8_t representativeSprite[NB_REPRESENTATIVE_SPRITE] = 
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void manageMachine()
{
    FILE* fichier;
    uint8_t valeur;
    fichier = fopen("./rom/Pong (1 player).ch8", "rb");
    struct t_processor* processor = newProcessor();
    loadRepresentativeSprite(processor);
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
        if (test == 1)
        {
            Display_update(processor->display);
            decrementTimer(processor);
            test = 0;
        }
        test++;
    }
}

void loadRepresentativeSprite(struct t_processor* processor)
{
    for (uint8_t i = 0 ; i < NB_REPRESENTATIVE_SPRITE ; i++)
        writeRAM(processor->RAM, i, representativeSprite[i]);
}