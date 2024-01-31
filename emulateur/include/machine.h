/**
 * \file  machine.h
 * \brief Gère l'émulateur et contient la boucle principale du programme
 *        Contient aussi la declarations de la structure \ref t_machine (l'émulateur)
 */

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

struct t_machine* initEmu()
{

}

/**
 * \relates t_machine
 * \brief   Alloue en memoire les elements de la structure \ref t_machine donnee en parametre
 * \param   machine emulateur a initialiser
 * \return  0 si la memoire a bien ete alouee, 1 si elle n'a pas ete allouee
 */
int initMachine(struct t_machine* machine);

/**
 * \relates t_machine
 * \brief   Librere la memoire des elements de la structure \ref t_machine
 * \param   machine emulateur a détruire
 */
void destroyMachine(struct t_machine* machine);

/**
 * \relates t_machine
 * \brief   Alloue la memoire pour une structure \ref t_machine ainsi que la memoire pour ses elements
 * \return  la structure allouée en mémoire et initialisée
 */
struct t_machine* newMachine();

/**
 * \relates t_machine
 * \brief   Librere la memoire de la structure \ref t_machine donnee en parametre
 * \param   machine emulateur a détruire
 */
void deleteMachine(struct t_machine* processor);

/**
 * \brief Demande a l'utilisateur quel ROM il veut lancer (et affiche les ROM dispo)
 * \return le nom de la rom choisi par l'utlisateur ou "" si il y a une erreur
 */
char* askRom(char* romName[50], unsigned int nbFile);

/**
 * \brief Cherche dans le dossier ROM le nom des ROMs
 * \return le nom de la rom choisi par l'utlisateur ou "" si il y a une erreur (return le return de \ref askRom)
 */
char* searchRomName()

/**
 * \brief Charge dans la RAM les sprites représentatifs
 * \param processor structure dans laquel se trouve la RAM
 */
void loadRepresentativeSprite(struct t_processor* processor);

/**
 * \brief Charge dans la RAM la ROM
 * \param processor structure dans laquel se trouve la RAM
 * \param romPath chemin vers la ROM à lancer
 */
void loadRom(struct t_processor* processor, char* romPath);

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