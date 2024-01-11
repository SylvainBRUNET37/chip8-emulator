#ifndef PROCESSOR_H
#define PROCESSOR_H

/**
 * \file  processor.h
 * \brief Contient les declarations de la structure \ref t_processor et des fonctions qui lui sont liee
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ram.h"

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
    * \brief Timer  pour le buzzer
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

    /**
    * \brief RAM du processeur
    */
    struct t_RAM* RAM;
};

/**
 * \relates t_processor
 * \brief   alloue en memoire les elements de la structure \ref t_processor donnee en parametre
 * \param   processor  Processeur de l'emulateur
 * \return  0 si la memoire a bien ete alouee, 1 si elle n'a pas ete allouee
 */
int initProcessor(struct t_processor* processor);

/**
 * \relates t_processor
 * \brief   librere la memoire des elements de la structure \ref t_processor
 * \param   processor  Processeur de l'emulateur
 */
void destroyProcessor(struct t_processor* processor);

/**
 * \relates t_processor
 * \brief   alloue la memoire pour une structure \ref t_processor ainsi que la memoire pour ses elements
 * \param   processor  Processeur de l'emulateur
 * \return  0 si la memoire a bien ete alouee, 1 si elle n'a pas ete allouee
 */
struct t_processor* newProcessor(void);

/**
 * \relates t_processor
 * \brief   librere la memoire de la structure \ref t_processor donnee en parametre
 * \param   processor  Processeur de l'emulateur
 */
void deleteProcessor(struct t_processor* processor);

/**
 * \relates t_processor
 * \brief   aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
 * \param   processor  Processeur de l'emulateur
 */
void fetchDecodeExecute(struct t_processor* processor);

/**
 * \relates t_processor
 * \brief   aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
 * \param   processor  Processeur de l'emulateur
 */
void fetch(struct t_processor* processor);

/**
 * \relates t_processor
 * \brief   aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
 * \param   processor  Processeur de l'emulateur
 */
void decode(struct t_processor* processor);

#endif