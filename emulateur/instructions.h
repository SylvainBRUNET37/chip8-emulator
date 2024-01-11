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
 * \brief Efface ce qu'il y a d'afficher sur l'écran
 * \param processor processeur sur lequel faire l'instruction
 * \return 0 si il n'y a pas eu d'erreur
 */
int clearDisplay_00E0(struct t_processor* processor);

/**
 * \brief Place le compteur de programme à l'adresse du sommet de la pile, puis soustrait 1 au pointeur de pile
 * \param processor processeur sur lequel faire l'instruction
 * \return 0 si il n'y a pas eu d'erreur
 */
int setPCtoTopStack_00EE(struct t_processor* processor);

/**
 * \brief Met le compteur du programme à nnn
 * \param processor processeur sur lequel faire l'instruction
 * \param nnn adresse à laquel mettre compteur d'instruction
 * \return 0 si il n'y a pas eu d'erreur
 */
int jumpTo_1nnn(struct t_processor* processor, uint16_t nnn);

/**
 * \brief Incrémente le pointeur de pile, puis place le PC actuel au sommet de la pile. Le PC est mis à nnn
 * \param processor processeur sur lequel faire l'instruction
 * \param nnn adresse à laquel mettre compteur d'instruction
 * \return 0 si il n'y a pas eu d'erreur
 */
int putPCtoTopStack_2nnn(struct t_processor* processor, uint16_t nnn);

/**
 * \brief Compare le registre Vx à kk et, s'ils sont égaux, incrémente le compteur de programme de 2
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de l'operande 1
 * \param kk indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int skipIfXequalKK_3xkk(struct t_processor* processor, uint8_t x, uint8_t kk);

/**
 * \brief Compare le registre Vx à kk et, s'ils ne sont pas égaux, incrémente le compteur de programme de 2
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de l'operande 1
 * \param kk indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int skipIfXnotEqualKK_4xkk(struct t_processor* processor, uint8_t x, uint8_t kk);

/**
 * \brief Compare le registre Vx au registre Vy et, s'ils sont égaux, incrémente le compteur de programme de 2
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de l'operande 1
 * \param y indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16
 */
int skipIfXequalY_5xy0(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Place la valeur kk dans le registre Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination
 * \param kk source
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int setXtoKK_6xkk(struct t_processor* processor, uint8_t x, uint8_t kk);

/**
 * \brief Place la somme de kk et Vx dans le registre Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination et de l'operande 1
 * \param kk operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int addXandKK_7xkk(struct t_processor* processor, uint8_t x, uint8_t kk);

/**
 * \brief Stocke la valeur du registe Vy dans le registre Vx    
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination
 * \param y indice de la source
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int setOperation_8xy0(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Fait l'operation OR sur la valeur des registres Vx et Vy et stocke le resultat dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de destination et de l'operande 1
 * \param y indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int orOperation_8xy1(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Fait l'operation AND sur la valeur des registres Vx et Vy et stocke le resultat dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination et de l'operande 1
 * \param y indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int andOperation_8xy2(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Fait l'operation XOR (OU exclusif) sur la valeur des registres Vx et Vy  et stocke le resultat dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination et de l'operande 1
 * \param y indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int exclusifOrOperation_8xy3(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Additionne la valeur des registres Vx et Vy et stocke le resultat dans Vx
 *        Si le resultat est plus grand que 8 bits (i.e., > 255,) 1 est mis dans le registe VF, sinon 0. Seulement le resultat sur 8 bits est gardé
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination et de l'operande 1
 * \param y indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int addOperation_8xy4(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Soustrait la valeur de Vx par la valeur de Vy et stocke le resultat dans Vx
 *        Si Vx > Vy, VF est mis à 1, sinon 0. Vy est ensuite soustrait de Vx, et les résultats sont stockés dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination et de l'operande 1
 * \param y indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int subOperation_8xy5(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Divise la valeur de Vx par 2
 *        Si le bit de poids faible de Vx est 1, VF est mis à 1, sinon 0. Vx est ensuite divisé par 2
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination et de l'operande 1
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16 (donc pas valide)
 */
int div2operation_8xy6(struct t_processor* processor, uint8_t x);

/**
 * \brief Soustrait la valeur de Vy par la valeur de Vx et stocke le resultat dans Vx
 *        Si Vy > Vx, VF est mis à 1, sinon 0. Ensuite, Vx est soustrait de Vy et les résultats sont stockés dans Vx.
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination et de l'operande 2
 * \param y indice de l'operande 1
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int subnOperation_8xy7(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief Multiplie la valeur de Vx par 2
 *        Si le bit le plus significatif de Vx est 1, VF est mis à 1, sinon à 0. Vx est ensuite multiplié par 2.
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination et de l'operande 1
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16 (donc pas valide)
 */
int mul2operation_8xyE(struct t_processor* processor, uint8_t x);

/**
 * \brief Si Vx n'est pas égal à Vy, saute la prochaine instruction
 *        Les valeurs de Vx et Vy sont comparées, et si elles ne sont pas égales, le compteur de programme est augmenté de 2
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de l'operande 1
 * \param y indice de l'operande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x ou y superieur à 16 (donc pas valide)
 */
int skipNextinstruction_9xy0(struct t_processor* processor, uint8_t x, uint8_t y);

/**
 * \brief La valeur nnn est mise dans le registre I
 * \param processor processeur sur lequel faire l'instruction
 * \param nnn valeur a mettre dans le registre I
 * \return 0 si il n'y a pas eu d'erreur
 */
int setIvalue_Annn(struct t_processor* processor, uint16_t nnn);

/**
 * \brief Le compteur de programme est réglé sur nnn plus la valeur de V0
 * \param processor processeur sur lequel faire l'instruction
 * \param nnn valeur à additionner avec V0
 * \return 0 si il n'y a pas eu d'erreur
 */
int jumpTo_Bnnn(struct t_processor* processor, uint16_t nnn);

/**
 * \brief Génère un nombre aléatoire compris entre 0 et 255, qui est ensuite "ANDé" avec la valeur kk
 *        Les résultats sont stockés dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice du registre où doit être stocké le resultat
 * \param kk indice de l'opérande 2 utiliser pour le ET
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int setRandom_Cxkk(struct t_processor* processor, uint8_t x, uint8_t kk);

/**
 * \brief Afficher un sprite de n octets commençant à l'emplacement de mémoire I à (Vx, Vy) et définir VF = collision
 *        Les résultats sont stockés dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x coordonnée en abscisse où afficher le sprite
 * \param y coordonnée en ordonnée où afficher le sprite
 * \param n nombre d'octets à lire à partir de l'adresse stockée dans le registre I
 * \return 0 si il n'y a pas eu d'erreur, 1 si x, y et/ou z superieur à 16
 */
int displaySprite_Dxyn(struct t_processor* processor, uint8_t x, uint8_t y, uint8_t n);

/**
 * \brief Sauter l'instruction suivante si la touche ayant la valeur Vx est enfoncée
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice du registre qui contient la valeur à comparer
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int jumpIfKeyPressed_Ex9E(struct t_processor* processor, uint8_t x);

/**
 * \brief Sauter l'instruction suivante si la touche ayant la valeur Vx n'est pas enfoncée
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice du registre qui contient la valeur à comparer
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int jumpIfKeyNotPressed_ExA1(struct t_processor* processor, uint8_t x);

/**
 * \brief La valeur de DT est placée dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int setXtoDL_Fx07(struct t_processor* processor, uint8_t x);

/**
 * \brief Attendre qu'une touche soit utilisée et enregistre sa valeur dans Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la destination
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int waitKeyPressed(struct t_processor* processor, uint8_t x);

/**
 * \brief La valeur de Vx est placée dans DT
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice du registre où la valeur doit être placer dans DT
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int setDTtoX_Fx18(struct t_processor* processor, uint8_t x);

/**
 * \brief La valeur de Vx est placée dans ST
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice du registre où la valeur doit être placer dans ST
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int setSTtoX_Fx15(struct t_processor* processor, uint8_t x);

/**
 * \brief Les valeurs de I et Vx sont additionnées et les résultats sont stockés dans I
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de l'opérande 2
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int addIandX_Fx1E(struct t_processor* processor, uint8_t x);

/**
 * \brief La valeur de I est fixée à l'emplacement du sprite hexadécimal correspondant à la valeur de Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la valeur de Vx
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int setItoSpriteX_Fx29(struct t_processor* processor, uint8_t x);

/**
 * \brief Prend la valeur décimale de Vx et place le chiffre des centaines en mémoire à l'emplacement I, 
 *        le chiffre des dizaines à l'emplacement I+1 et le chiffre des unités à l'emplacement I+2
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la valeur de Vx
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int setXtoI_Fx33(struct t_processor* processor, uint8_t x);

/**
 * \brief Copie les valeurs des registres V0 à Vx dans la mémoire, à partir de l'adresse I
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la valeur de Vx
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int storeRegisterInMemory_Fx55(struct t_processor* processor, uint8_t x);

/**
 * \brief Lit les valeurs de la mémoire à partir de l'emplacement I dans les registres V0 à Vx
 * \param processor processeur sur lequel faire l'instruction
 * \param x indice de la valeur de Vx
 * \return 0 si il n'y a pas eu d'erreur, 1 si x superieur à 16
 */
int readMemory_Fx65(struct t_processor* processor, uint8_t x);

#endif