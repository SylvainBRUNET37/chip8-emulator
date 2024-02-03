/**
 * \file  rom.h
 * \brief Contient la déclaration des fonctions liées à lié à la ROM
 */

#ifndef ROM_H
#define ROM_H

#include "ram.h"

/**
 * \brief Demande a l'utilisateur quel ROM il veut lancer (et affiche les ROM disponibles)
 * \param romName tableau contenant le nom des ROM
 * \param nbFile nombre de ROM dans le dossier
 * \return le nom de la rom choisi par l'utlisateur ou "" si il y a une erreur
 */
char* askRom(char* romName[50], unsigned int nbFile);

/**
 * \brief Cherche dans le dossier ROM le nom des ROMs
 * \return le nom de la rom choisi par l'utlisateur ou "" si il y a une erreur (return le return de \ref askRom)
 */
char* searchRomName();

/**
 * \brief Charge dans la RAM la ROM
 * \param processor structure dans laquel se trouve la RAM
 * \param romPath chemin vers la ROM à lancer
 */
void loadRom(struct t_RAM* RAM, char* romPath);

#endif