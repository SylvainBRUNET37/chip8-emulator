/**
 * \file  ram.h
 * \brief Contient la declarations de la structure \ref t_RAM la définition des fonctions liée à celle-ci
 */

#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * \struct t_RAM
 * \brief  RAM de l'emulateur
 */
struct t_RAM
{
    /**
    * \brief Memoire de l'emulateur
    */
    uint8_t* ram;
};

/**
 * \relates t_RAM
 * \brief   Alloue en mémoire la ram d'une structure \ref t_RAM donnee en parametre
 * \param   RAM  RAM de l'emulateur
 * \return  0 si la memoire a bien ete allouée, 1 si elle n'a pas ete allouée
 */
int initRAM(struct t_RAM* RAM);

/**
 * \relates t_RAM
 * \brief   Librere la mémoire de la ram de la structure \ref t_RAM
 * \param   RAM  RAM de l'emulateur
 */
void destroyRAM(struct t_RAM* RAM);

/**
 * \relates t_RAM
 * \brief   Alloue la mémoire pour une structure \ref t_RAM ainsi que la mémoire pour sa RAM
 * \param   RAM  RAM de l'emulateur
 * \return  0 si la mémoire a bien ete alouee, 1 si elle n'a pas ete allouée
 */
struct t_RAM* newRAM(void);

/**
 * \relates t_RAM
 * \brief   Libère la mémoire de la structure \ref t_RAM donnée en paramètre
 * \param   RAM  RAM de l'emulateur
 */
void deleteRAM(struct t_RAM* RAM);

/**
 * \relates t_RAM
 * \brief   Ecrit la valeur donnée a l'adresse donnée dans la RAM
 * \param   RAM  RAM de l'emulateur
 * \param   adr  adresse où écrire la valeur donnée
 * \param   val  valeur a mettre dans la RAM
 * \return  0 si la valeur a bien été écrite, 1 si la RAM donnée est NULL
 */
int writeRAM(struct t_RAM* RAM, uint16_t adr, uint8_t val);

/**
 * \relates t_RAM
 * \brief   Lit dans en RAM la valeur à l'adresse donnée
 * \param   RAM  RAM de l'emulateur
 * \param   adr  adresse où lire la valeur donnée
 * \return  la valeur en RAM à l'adresse donnée
 */
uint8_t readRAM(struct t_RAM* RAM, uint16_t adr);

#endif