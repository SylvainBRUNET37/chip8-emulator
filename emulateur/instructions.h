#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

/**
 * \file  instructions.h
 * \brief Contient les instructions Chip-8
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "processor.h"

/**
 * \brief Stocke la valeur du registe Vy dans le registre Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination
 * \param y source
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int setOperation_8xy0(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Fait l'operation OR sur la valeur des registres Vx et Vy et stocke le resultat dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \param y operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int orOperation_8xy1(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Fait l'operation AND sur la valeur des registres Vx et Vy et stocke le resultat dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \param y operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int andOperation_8xy2(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Fait l'operation XOR (OU exclusif) sur la valeur des registres Vx et Vy  et stocke le resultat dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \param y operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int exclusifOrOperation_8xy3(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Additionne la valeur des registres Vx et Vy et stocke le resultat dans Vx
 *        Si le resultat est plus grand que 8 bits (i.e., > 255,) 1 est mis dans le registe VF, sinon 0. Seulement le resultat sur 8 bits est gardé
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \param y operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int addOperation_8xy4(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Soustrait la valeur de Vx par la valeur de Vy et stocke le resultat dans Vx
 *        ///
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \param y operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int subOperation_8xy5(struct t_processor* processor, uint8_t x, uint8_t y);

#endif