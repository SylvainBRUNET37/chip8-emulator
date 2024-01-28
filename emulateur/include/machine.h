#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "processor.h"

#define NB_SPRITE_REPRESENTATIF = 80 // Taille du tableau des sprites des chiffres hexa

/**
 * \file  machine.h
 * \brief Gère l'émulateur et charge la ROM en ram
 */
void manageMachine();

#endif