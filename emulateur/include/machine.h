/**
 * \file  machine.h
 * \brief Contient aussi la declarations de la structure \ref t_machine (l'émulateur) et des fonctions qui lui sont liée
 */

#ifndef MACHINE_H
#define MACHINE_H

#include "instructions.h"

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
 * \memberof t_machine
 * \brief   Alloue en mémoire les élements de la structure \ref t_machine donnee en parametre
 * \param   machine emulateur à initialiser
 * \return  0 si la memoire a bien été allouée, 1 si elle n'a pas ete allouee
 */
int initMachine(struct t_machine* machine);

/**
 * \memberof t_machine
 * \brief   Librère la memoire des éléments de la structure \ref t_machine
 * \param   machine emulateur a détruire
 */
void destroyMachine(struct t_machine* machine);

/**
 * \memberof t_machine
 * \brief   Alloue de la mémoire pour une structure \ref t_machine ainsi que pour ses éléments
 * \return  la structure allouée en mémoire et initialisée ou NULL si elle n'a pas pu être allouée
 */
struct t_machine* newMachine();

/**
 * \memberof t_machine
 * \brief   Libère la mémoire de la structure \ref t_machine donnée en paramètre
 * \param   machine emulateur a détruire
 */
void deleteMachine(struct t_machine* processor);

/**
 * \brief Charge dans la RAM les sprites représentatifs
 * \param processor la RAM où mettre les sprites
 */
void loadRepresentativeSprite(struct t_RAM* RAM);

/**
 * \brief Gère le fetch decode execute et incrémente le programme counter de 2
 *        Fetch : Va chercher en mémoire à l'adresse du PC l'instruction a exécuter 
 *        Decode : Décode l'instruction pour savoir laquel c'est et récupère les valeurs utiles pour exécuter l'instruction (x, y, nnn...)
 *        Execute : Exécute la fonction liée à l'instruction
 * \param machine strcuture de l'émulateur qui contient les structures (display, processeur...) utilisées pour les instuctions
 * \return 0 si une instruction a été trouvée, 1 si x ou y > 16 (pas valide), 2 si l'instruction est incorrecte
 */
int fetchDecodeExecute(struct t_machine* machine);

#endif