#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "processor.h"

#define NB_REPRESENTATIVE_SPRITE 80 // Taille du tableau des sprites des chiffres hexa

/**
 * \brief Gère la machine
 */
void manageMachine();

/**
 * \brief Charge dans la RAM les sprites représentatifs
 * \param processor processeur sur lequel faire l'instruction
 */
void loadRepresentativeSprite(struct t_processor* processor);

#endif