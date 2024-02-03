/**
 * \file  emulator.c
 * \brief Gère l'émulateur et la boucle principale du programme
 */

#include "./include/emulator.h"

struct t_machine* initEmulator()
{
    // Initialisation la vidéo et l'audio
    if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)) 
    { 
        printf("Impossible d'initialiser la SDL : %s.\n", SDL_GetError());
        return NULL;
    }

    // Créé et initialise la machine virtuel
    struct t_machine* machine = newMachine();
    if (machine == NULL)
    {
        printf("L'emulateur n'a pas pu etre cree/initialise.\n");
        return NULL;
    }

    // Demande à l'utilisateur quel ROM il veut lancer
    char* romPath = searchRomName();
    
    // Charge en RAM la ROM
    loadRom(machine->RAM, romPath);
    
    return machine;
}

int mainLoop(struct t_machine* machine)
{
    unsigned short timerCounter = 0;
    int error = 0;
    while(1)
    {
        // Endort le programme pendant 2ms pour que le fetch/decode/execute se lance 500 fois par seconde (500Hz)
        SDL_Delay(2);
        error = fetchDecodeExecute(machine);
        if (error == 1)
        {
            printf("La valeur de x ou y donnee a la fonction de l'instruction n'est pas valide.\n");
            return 1;
        }
        else if (error == 2)
        {
            printf("L'instruction recuperee n'est pas valide.\n");
            return 1;
        }
            
        // Tous les 8 tours de boucle (fréquence : (500/8)Hz ~= 60Hz), décrémente les timers et met à jour l'affichage
        if (timerCounter == 1)
        {
            if (Display_update(machine->display) == 1)
            {
                printf("Une fonction de la librairie SDL n'a pas abouti.\n");
                return 1;
            }
            decrementTimer(machine->processor);
            timerCounter = 0;
        }
        timerCounter++;
    }
    return 0;
}