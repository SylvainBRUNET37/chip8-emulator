/**
 * \file  instructions.c
 * \brief Contient la définition des fonction effectuant les instructions Chip-8
 */

#include "./include/instructions.h"

void CLS_00E0(struct Display* display)
{
    Display_CLS(display);
}

void RET_00EE(struct t_processor* processor)
{
    // Place le compteur de programme à l'adresse du sommet de la pile
    processor->programCounter = processor->stack[processor->stackPointer];
    // Soustrait 1 au pointeur de pile
    processor->stackPointer--;
}

void JP_1nnn(struct t_processor* processor, uint16_t nnn)
{
    // Met le compteur de programme à nnn
    processor->programCounter = nnn;
}

void CALL_2nnn(struct t_processor* processor, uint16_t nnn)
{
    // Ajoute 1 au pointeur de pile
    processor->stackPointer++;
    // Place le PC actuel au sommet de la pile
    processor->stack[processor->stackPointer] = processor->programCounter;
    // Le PC est mis à nnn
    processor->programCounter = nnn;
}

int SE_3xkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x >= 16)
        return 1;
    // Compare les registres Vx et kk et s'ils sont égaux, incrémente le compteur de programme de 2    
    if (processor->generalRegister[x] == kk)
        processor->programCounter += 2;
    return 0;
}

int SNE_4xkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x >= 16)
        return 1;
    // Compare le registre Vx à kk et s'ils ne sont pas égaux, incrémente le compteur de programme de 2
    if (processor->generalRegister[x] != kk)
        processor->programCounter += 2;
    return 0;
}

int SE_5xy0(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Compare les registres Vx et Vy et s'ils sont égaux, incrémente le compteur de programme de 2
    if (processor->generalRegister[x] == processor->generalRegister[y])
        processor->programCounter += 2;
    return 0;
}

int LD_6xkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x >= 16)
        return 1;
    // Place la valeur kk dans le registre Vx
    processor->generalRegister[x] = kk;
    return 0;
}

int ADD_7xkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x >= 16)
        return 1;
    // Ajoute la valeur kk à la valeur du registre Vx
    processor->generalRegister[x] += kk;
    return 0;
}

int LD_8xy0(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Enregistre la valeur du registre Vy dans le registre Vx
    processor->generalRegister[x] = processor->generalRegister[y];
    return 0;
}

int OR_8xy1(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Effectue un OU bit à bit sur les valeurs de Vx et Vy puis stocke le résultat dans Vx
    processor->generalRegister[x] = ((processor->generalRegister[x]) | (processor->generalRegister[y]));
    // Réinitialise VF
    processor->generalRegister[15] = 0;
    return 0;
}

int AND_8xy2(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Effectue un ET bit à bit sur les valeurs de Vx et Vy puis stocke le résultat dans Vx.
    processor->generalRegister[x] = ((processor->generalRegister[x]) & (processor->generalRegister[y]));
    // Réinitialise VF
    processor->generalRegister[15] = 0;
    return 0;
}

int XOR_8xy3(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Effectue un OU exclusif bit à bit sur les valeurs de Vx et Vy puis stocke le résultat dans Vx.
    processor->generalRegister[x] = ((processor->generalRegister[x]) ^ (processor->generalRegister[y]));
    // Réinitialise VF
    processor->generalRegister[15] = 0;
    return 0;
}

int ADD_8xy4(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;

    // Créé une variable temporaire stockant Vx pour pouvoir l'étudier après l'opération
    uint8_t temp = processor->generalRegister[x];
    // Additionne Vx et Vy et stocke le résultat dans Vx
    processor->generalRegister[x] += processor->generalRegister[y];
    
    // Si le résultat est supérieur à 8 bits (c'est-à-dire > 255), VF est mis à 1, sinon 0
    if ((temp + processor->generalRegister[y]) > 0xFF)
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;
    return 0;
}

int SUB_8xy5(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    
    // Créé une variable temporaire stockant Vx pour pouvoir comparer sa valeur à Vy après l'opération
    uint8_t temp = processor->generalRegister[x];
    // Soustrait de Vy à Vx et stocke le résultat dans Vx
    processor->generalRegister[x] -= processor->generalRegister[y];
    
    // Si Vx > Vy, VF est mis à 1, sinon 0
    if (temp >= processor->generalRegister[y])
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;

    return 0;
}


int SHR_8xy6(struct t_processor* processor, uint8_t x, u_int8_t y)
{
    if (x >= 16)
        return 1;

    // Créé une variable temporaire stockant Vx pour pouvoir étudier son bit de poid faible après l'opération
    uint8_t temp = processor->generalRegister[x];
    // Divise Vx par deux
    processor->generalRegister[x] = processor->generalRegister[y] >> 1;

    // Si le bit de poids faible de Vx est égal à 1, VF est mis à 1, sinon 0
    if ((temp & 0x01) == 0x01)
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;
    return 0;
}

int SUBN_8xy7(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;

    // Créé une variable temporaire stockant Vy pour pouvoir comparer sa valeur à Vx après l'opération
    uint8_t temp = processor->generalRegister[y];
    // Vx est soustrait de Vy et le résultat est stocké dans Vx
    processor->generalRegister[x] = processor->generalRegister[y] - processor->generalRegister[x];
    
    // Si Vy > Vx, VF est mis à 1, sinon 0
    if (temp > processor->generalRegister[x])
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;
    return 0;
}

int SHL_8xyE(struct t_processor* processor, uint8_t x, u_int8_t y)
{
    if (x >= 16)
        return 1;

    // Créé une variable temporaire stockant Vx pour pouvoir étudier son poid fort après l'opération
    uint8_t temp = processor->generalRegister[x];
    // Multiplie Vx par 2
    processor->generalRegister[x] = processor->generalRegister[y] << 1;

    
    // Si le bit de poid le plus fort de Vx est égale à 1, met le reste dans VF
    if ((temp & 0x80) == 0x80)
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;
    return 0;
}

int SNE_9xy0(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Les valeurs de Vx et Vy sont comparées et si elles ne sont pas égales, le compteur de programme est augmenté de 2
    if (processor->generalRegister[x] != processor->generalRegister[y])
        processor->programCounter += 2;
    return 0;
}

void LD_Annn(struct t_processor* processor, uint16_t nnn)
{
    // Fixe la valeur du registre I à nnn
    processor->IRegister = nnn;
}

void JP_Bnnn(struct t_processor* processor, uint16_t nnn)
{
    // Le compteur de programme est réglé sur nnn plus la valeur de V0
    processor->programCounter = nnn + processor->generalRegister[0];
}

int RND_Cxkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x >= 16)
        return 1;
    // Génère un nombre aléatoire compris entre 0 et 255 qui est ensuite "ANDé" avec la valeur kk
    uint8_t temp = (uint8_t)((rand() % 0xFF) & (kk));
    // Le résultat est stocké dans Vx
    processor->generalRegister[x] = temp;
    return 0;
}

int DRW_Dxyn(struct t_processor* processor, struct t_RAM* RAM, struct Display* display, uint8_t x, uint8_t y, uint8_t n)
{
    if (x >= 16 || y >= 16 || n >= 16)
        return 1;

    uint8_t temp = 0;
    struct Sprite sprite;
    Sprite_init(&sprite,n);
    // Lit n octets en mémoire à partir de l'adresse stockée dans I et ajoute
    for (uint16_t i = 0 ; i < n ; i++)
    {
        temp = readRAM(RAM, processor->IRegister+i);
        // Ajoute l'octet au sprite
        Sprite_add(&sprite, temp);
    }
    // Affiche le sprite aux coordonnées (Vx, Vy)
    Display_DRW(display, &sprite, processor->generalRegister[x], processor->generalRegister[y], &processor->generalRegister[15]);

    Sprite_destroy(&sprite);
    return 0;
}

int SKP_Ex9E(struct t_processor* processor, struct Keyboard* keyboard, uint8_t x)
{
    if (x >= 16)
        return 1;
    int state = 0;
    // Vérifie le clavier et si la touche correspondant à la valeur de Vx est préssée, PC est augmenté de 2
    int error = Keyboard_get(keyboard, processor->generalRegister[x], &state);
    if (error == 1)
        return 1;
    if (state == 1)
        processor->programCounter += 2;
    return 0;
}

int SKNP_ExA1(struct t_processor* processor, struct Keyboard* keyboard, uint8_t x)
{
    if (x >= 16)
        return 1;
    int state = 0;
    // Vérifie le clavier et si la touche correspondant à la valeur de Vx n'est pas préssée, PC est augmenté de 2
    int error = Keyboard_get(keyboard, processor->generalRegister[x], &state);
    if (error == 1)
        return 1;
    if (state == 0)
        processor->programCounter += 2;
    return 0;
}

int LD_Fx07(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    // La valeur de DT est placée dans Vx    
    processor->generalRegister[x] = processor->delayTimerRegister;
    return 0;
}

int LD_Fx0A(struct t_processor* processor, struct Keyboard* keyboard, uint8_t x)
{
    if (x >= 16)
        return 1;
    // Toute exécution s'arrête jusqu'à ce qu'une touche soit pressée, puis la valeur de cette touche est stockée dans Vx
    Keyboard_wait(keyboard, &processor->generalRegister[x]);
    return 0;
}

int LD_Fx15(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    // La valeur de Vx est placée dans DT 
    processor->delayTimerRegister = processor->generalRegister[x];
    return 0;
}

int LD_Fx18(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    // La valeur de Vx est placée dans ST 
    processor->soundTimerRegister = processor->generalRegister[x];
    return 0;
}

int ADD_Fx1E(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;

    // Les valeurs du registre I et Vx sont additionnées et le résultat est stocké dans le registre I
    processor->IRegister += processor->generalRegister[x];
    return 0;
}

int LD_Fx29(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    // La valeur de I est fixée à l'emplacement du sprite correspondant à la valeur de Vx
    processor->IRegister = 5*processor->generalRegister[x];
    return 0;
}

int LD_Fx33(struct t_processor* processor, struct t_RAM* RAM, uint8_t x)
{
    if (x >= 16)
        return 1;

    uint8_t temp = processor->generalRegister[x];

    // Prend la valeur décimale de Vx et place le chiffre des centaines en mémoire à l'emplacement I
    writeRAM(RAM, processor->IRegister, (temp/100));
    temp %= 100;
    // Fait la même chose avec le chiffre des dixaines
    writeRAM(RAM, processor->IRegister+1, (temp/10));
    temp %= 10;
    // Fait la même chose avec le chiffre des unités
    writeRAM(RAM, processor->IRegister+2, temp);
    return 0; 
}

int LD_Fx55(struct t_processor* processor, struct t_RAM* RAM, uint8_t x)
{
    if (x >= 16)
        return 1;
    // Copie les valeurs des registres V0 à Vx dans la mémoire en commençant à l'adresse I, et incrémente le registre I à chaque tour de boucle
    for (uint16_t i = 0 ; i <= x ; i++)
    {
        writeRAM(RAM, processor->IRegister, processor->generalRegister[i]);
        processor->IRegister += 1;
    }
    return 0;
}

int LD_Fx65(struct t_processor* processor, struct t_RAM* RAM, uint8_t x)
{
    if (x >= 16)
        return 1;
    // Lit les valeurs de la mémoire à partir de l'emplacement I dans les registres V0 à Vx, et incrémente le registre I à chaque tour de boucle
    for (uint16_t i = 0 ; i <= x ; i++)
    {
        processor->generalRegister[i] = readRAM(RAM, processor->IRegister);
        processor->IRegister += 1;
    }
    return 0;
}
