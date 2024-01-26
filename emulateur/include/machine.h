#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "processor.h"

#define NB_SPRITE_REPRESENTATIF = 80

/**
 * \file  machine.h
 * \brief Gère l'émulateur
 */
void manageMachine();

#endif