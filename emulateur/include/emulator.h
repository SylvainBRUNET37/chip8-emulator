/**
 * \file  emulator.h
 * \brief Gère l'émulateur et la boucle principale du programme
 */

#ifndef EMULATOR_H
#define EMULATOR_H

#include "rom.h"
#include "machine.h"

/**
 * \brief Initialise l'émulateur
 * \return la structure allouée en mémoire et initialisée ou NULL si elle n'a pas pu être allouée
 */
struct t_machine* initEmulator();

/**
 * \brief Lance la boucle principale
 * \param machine emulateur
 * \return 
 */
int mainLoop(struct t_machine* machine);

#endif