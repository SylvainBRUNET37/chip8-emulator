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
 *        Si Vx > Vy, VF est mis à 1, sinon 0. Vy est ensuite soustrait de Vx, et les résultats sont stockés dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \param y operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int subOperation_8xy5(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Divise la valeur de Vx par 2
 *        Si le bit de poids faible de Vx est 1, VF est mis à 1, sinon 0. Vx est ensuite divisé par 2
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16 (donc pas valide)
 */
int div2Operation_8xy6(struct t_processor* processor, uint8_t x);

/**
 * \brief Soustrait la valeur de Vy par la valeur de Vx et stocke le resultat dans Vx
 *        Si Vy > Vx, VF est mis à 1, sinon 0. Ensuite, Vx est soustrait de Vy et les résultats sont stockés dans Vx.
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 2
 * \param y operande 1
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int subnOperation_8xy7(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Multiplie la valeur de Vx par 2
 *        Si le bit le plus significatif de Vx est 1, VF est mis à 1, sinon à 0. Vx est ensuite multiplié par 2.
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16 (donc pas valide)
 */
int mul2Operation_8xyE(struct t_processor* processor, uint8_t x);

/**
 * \brief Multiplie la valeur de Vx par 2
 *        Les valeurs de Vx et Vy sont comparées, et si elles ne sont pas égales, le compteur de programme est augmenté de 2
 * \param processor processeur sur lequel faire l'instruction
 * \param x destination et operande 1
 * \param y operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int skipNextinstruction_9xy0(struct t_processor* processor, uint8_t x, uint8_t y); // PAS FAITE
 

#endif