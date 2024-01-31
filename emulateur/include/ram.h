#ifndef RAM_H
#define RAM_H

/**
 * \file  ram.h
 * \brief Contient la declarations de la structure \ref t_RAM et des fonctions qui lui sont liee
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
 * \brief   Alloue en memoire la ram d'une structure \ref t_RAM donnee en parametre
 * \param   RAM  RAM de l'emulateur
 * \return  0 si la memoire a bien ete alouee, 1 si elle n'a pas ete allouee
 */
int initRAM(struct t_RAM* RAM);

/**
 * \relates t_RAM
 * \brief   Librere la memoire de la ram de la structure \ref t_RAM
 * \param   RAM  RAM de l'emulateur
 */
void destroyRAM(struct t_RAM* RAM);

/**
 * \relates t_RAM
 * \brief   Alloue la memoire pour une structure \ref t_RAM ainsi que la memoire pour sa RAM
 * \param   RAM  RAM de l'emulateur
 * \return  0 si la memoire a bien ete alouee, 1 si elle n'a pas ete allouee
 */
struct t_RAM* newRAM(void);

/**
 * \relates t_RAM
 * \brief   Librere la memoire de la structure \ref t_RAM donnee en parametre
 * \param   RAM  RAM de l'emulateur
 */
void deleteRAM(struct t_RAM* RAM);

/**
 * \relates t_RAM
 * \brief   Ecrit la valeur donnee a l'adresse donnee dans la RAM donnee
 * \param   RAM  RAM de l'emulateur
 * \param   adr  adresse ou on veut ecrire la valeur donnee
 * \param   val  ecrit a l'adresse donnee cette valeur
 * \return  0 si la valeur a bien ete ecrite, 1 si la RAM donnee est NULL
 */
int writeRAM(struct t_RAM* RAM, uint16_t adr, uint8_t val);

/**
 * \relates t_RAM
 * \brief   Lit dans \ref RAM la valeur donee
 * \param   RAM  RAM de l'emulateur
 * \param   adr  adresse ou on veut lire la valeur donnee
 * \return  la valeur de l'adresse donnee
 */
uint8_t readRAM(struct t_RAM* RAM, uint16_t adr);

#endif