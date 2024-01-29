#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "processor.h"

#define NB_REPRESENTATIVE_SPRITE 80 // Taille du tableau des sprites des chiffres hexa

/**
 * \struct t_machine
 * \brief  Emulateur de la machine
 */
struct t_machine
{
    /**
    * \brief Processeur de la machine
    */
    struct t_processor* processor;

    /**
    * \brief RAM de la machine
    */
    struct t_RAM* RAM;

    /**
    * \brief Emule un écran monochrome 64x32
    */
    struct Display* display;

    /**
    * \brief Emule un haut-parleur monotone (buzzer)
    */
    struct Speaker* speaker;

    /**
    * \brief Emule un clavier à 16 touches
    */
    struct Keyboard* keyboard;
};

/**
 * \brief Gère la machine
 */
void manageMachine();

/**
 * \brief Gère le fetch decode execute et incrémente le programme counter de 2
 *        Fetch : Va chercher en mémoire à l'adresse du PC l'instruction a exécuter 
 *        Decode : Décode l'instruction pour savoir laquel c'est et récupère les valeurs utiles pour exécuter l'instruction (x, y, nnn...)
 *        Execute : Exécute la fonction liée à l'instruction
 */
void fetchDecodeExecute(struct t_processor* processor);

/**
 * \brief Charge dans la RAM les sprites représentatifs
 * \param processor structure dans laquel se trouve la RAM
 */
void loadRepresentativeSprite(struct t_processor* processor);

/**
 * \brief Charge dans la RAM la ROM
 * \param processor structure dans laquel se trouve la RAM
 */
void loadRom(struct t_processor* processor);

#endif