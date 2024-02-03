/**
 * \file  main.c
 * \brief Lance le jeu et le ferme quand l'utilisateur à fini de jouer où qu'il y a une erreur
 */

#include "./include/emulator.h"

int main()
{
    // Intialise l'émulateur puis lance la boucle principale
    struct t_machine* machine = initEmulator();
    if (machine == NULL)
        return 1;
    if (mainLoop(machine) == 1)
        return 1;

    // Ferme la fenêtre de jeu
    SDL_Quit();
    return 0;
}