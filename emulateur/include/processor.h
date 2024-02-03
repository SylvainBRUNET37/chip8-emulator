/**
 * \file  processor.h
 * \brief Contient la declarations de la structure \ref t_processor et les déclarations fonctions qui lui sont liee
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#define nbGeneralRegister 16
#define nbStackElement 16

/**
 * \struct t_processor
 * \brief  Processeur de l'emulateur
 */
struct t_processor
{
    /**
    * \brief Contient les (16) registres du processeur
    */
    uint8_t generalRegister[nbGeneralRegister];

    /**
    *\brief Register I (contient generalement des adresses)
    */
    uint16_t IRegister;

    /**
    * \brief Timer
    */
    uint8_t delayTimerRegister;

    /**
    * \brief Timer pour le buzzer
    */
    uint8_t soundTimerRegister;

    /**
    *\brief Pile du processeur
    */
    uint16_t stack[nbStackElement];

    /**
    * \brief Compteur de programme (contient l'adresse a executer)
    */
    uint16_t programCounter;

    /**
    * \brief Pointeur sur le haut de la pile (contient l'adresse du 1er element de la pile)
    */
    uint8_t stackPointer;
};

/**
 * \memberof t_processor
 * \brief   Met à 0 toutes les variables de la structure \ref t_processor. 
 *          Cette fonction remplace init et destroy car il n'y a pas d'allocation à faire ou de mémoire à libérer (les deux ferraient la même chose)
 * \param   processor Processeur de l'emulateur à (ré)initialiser
 */
void resetProcessor(struct t_processor* processor);

/**
 * \memberof t_processor
 * \brief   Alloue la mémoire pour une structure \ref t_processor ainsi que la mémoire pour ses élements
 * \return  la structure allouée ou NULL si l'allocation n'a pas pu être faites
 */
struct t_processor* newProcessor(void);

/**
 * \memberof t_processor
 * \brief   Libère la mémoire de la structure \ref t_processor donnée en paramètre
 * \param   processor  Processeur de l'emulateur
 */
void deleteProcessor(struct t_processor* processor);

/**
 * \memberof t_processor
 * \brief   Décrémente de 1 le delay timer et le sound timer si ils ne sont pas à 0
 * \param   processor  Processeur de l'emulateur
 */
void decrementTimer(struct t_processor* processor);

#endif