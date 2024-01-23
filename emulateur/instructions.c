#include "./include/instructions.h"

int CLS_00E0(struct t_processor* processor)
{
    Display_CLS(processor->display);
    return 0;
}

int RET_00EE(struct t_processor* processor)
{
    // Place le compteur de programme à l'adresse du sommet de la pile
    processor->programCounter = processor->stack[processor->stackPointer];
    // Soustrait 1 au pointeur de pile
    processor->stackPointer--;
    return 0;
}

int JP_1nnn(struct t_processor* processor, uint16_t nnn)
{
    // Met le compteur de programme à nnn
    processor->programCounter = nnn;
    return 0;
}

int CALL_2nnn(struct t_processor* processor, uint16_t nnn)
{
    // Ajoute 1 au pointeur de pile
    processor->stackPointer++;
    // Place le PC actuel au sommet de la pile
    processor->stack[processor->stackPointer] = processor->programCounter;
    // Le PC est mis à nnn
    processor->programCounter = nnn;
    return 0;
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
    return 0;
}

int AND_8xy2(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Effectue un ET bit à bit sur les valeurs de Vx et Vy puis stocke le résultat dans Vx.
    processor->generalRegister[x] = ((processor->generalRegister[x]) & (processor->generalRegister[y]));
    return 0;
}

int XOR_8xy3(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Effectue un OU exclusif bit à bit sur les valeurs de Vx et Vy puis stocke le résultat dans Vx.
    processor->generalRegister[x] = ((processor->generalRegister[x]) ^ (processor->generalRegister[y]));
    return 0;
}

int ADD_8xy4(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Addictionne les valeurs de Vx et Vy
    uint16_t temp = x + y;
    // Si le résultat est supérieur à 8 bits (c'est-à-dire > 255), VF est mis à 1, sinon 0
    if (temp > 255)
    {
        // Stocke seulement les 8 bits les plus bas du résultat
        temp = (temp & 255);
        processor->generalRegister[15] = 1;
    }
    else
        processor->generalRegister[15] = 0;
    // Stocke le résultat dans Vx
    processor->generalRegister[x] = temp;
    return 0;
}

int SUB_8xy5(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Si Vx > Vy, VF est mis à 1, sinon 0
    if (processor->generalRegister[x] > processor->generalRegister[y])
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;
    // Soustrait de Vy à Vx et stocke le résultat dans Vx
    processor->generalRegister[x] -= processor->generalRegister[y];
    return 0;
}

int SHR_8xy6(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    // Si le bit de poids faible de Vx est égal à 1, VF est mis à 1, sinon 0
    if ((processor->generalRegister[x] & 1) == 1)
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;
    // Divise Vx par deux
    processor->generalRegister[x] /= 1;
    return 0;
}

int SUBN_8xy7(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    // Si Vy > Vx, VF est mis à 1, sinon 0
    if (processor->generalRegister[y] > processor->generalRegister[x])
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;
    // Vx est soustrait de Vy et le résultat est stocké dans Vx
    processor->generalRegister[x] = processor->generalRegister[y] - processor->generalRegister[x];
    return 0;
}

// JAI PAS COMMENTER A PARTIR DE LA
int SHL_8xyE(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    // Si le bit de poid le plus fort de Vx est égale à 1, met le reste dans VF
    if ((processor->generalRegister[x] & 0x80) == 1)
        processor->generalRegister[15] = 1;
    else
        processor->generalRegister[15] = 0;
    processor->generalRegister[x] <<= 1;
    return 0;
}

int SNE_9xy0(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x >= 16 || y >= 16)
        return 1;
    if (processor->generalRegister[x] != processor->generalRegister[y])
        processor->programCounter += 2;
    return 0;
}

int LD_Annn(struct t_processor* processor, uint16_t nnn)
{
    processor->IRegister = nnn;
    return 0;
}

int JP_Bnnn(struct t_processor* processor, uint16_t nnn)
{
    processor->programCounter = nnn + processor->generalRegister[0];
    return 0;
}

int RND_Cxkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x >= 16)
        return 1;
    uint8_t temp = rand() % (kk + 1);
    processor->generalRegister[x] = temp;
    return 0;
}

int DRW_Dxyn(struct t_processor* processor, uint8_t x, uint8_t y, uint8_t n)
{
    if (x >= 16 || y >= 16 || n >= 16)
        return 1;

    uint8_t temp = 0;
    struct Sprite sprite;
    Sprite_init(&sprite,n);
    for (unsigned int i = 0 ; i < n ; i++)
    {
        temp = processor->RAM->ram[processor->IRegister+i];
        Sprite_add(&sprite, temp);
    }
    Display_DRW(processor->display, &sprite, processor->generalRegister[x], processor->generalRegister[y], &processor->generalRegister[15]);
    Sprite_destroy(&sprite);
    return 0;
}

int SKP_Ex9E(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    uint8_t temp = 0;
    Keyboard_wait(processor->keyboard, &temp);
    if (temp == processor->generalRegister[x])
        processor->programCounter += 2;
    return 0;
}

int SKNP_ExA1(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    uint8_t temp = 0;
    Keyboard_wait(processor->keyboard, &temp);
    if (temp != processor->generalRegister[x])
        processor->programCounter += 2;
    return 0;
}

int LD_Fx07(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    processor->generalRegister[x] = processor->delayTimerRegister;
    return 0;
}

int LD_Fx0A(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;

    Keyboard_wait(processor->keyboard, &processor->generalRegister[x]);
    return 0;
}

int LD_Fx15(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    processor->soundTimerRegister = processor->generalRegister[x];
    return 0;
}

int LD_Fx18(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    processor->delayTimerRegister = processor->generalRegister[x];
    return 0;
}

int ADD_Fx1E(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    processor->IRegister += processor->generalRegister[x];
    return 0;
}

int LD_Fx29(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;
    processor->IRegister = processor->generalRegister[x];
    return 0;
}

int LD_Fx33(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;

    uint8_t temp = processor->generalRegister[x];

    processor->RAM->ram[processor->IRegister] = temp / 100;
    temp %= 100;
    processor->RAM->ram[processor->IRegister+1] = temp / 10;
    temp %= 10;
    processor->RAM->ram[processor->IRegister+2] = temp;
    return 0; 
}

int LD_Fx55(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;

    for (unsigned int i = 0 ; i <= x ; i++)
        processor->RAM->ram[processor->IRegister+i] = processor->generalRegister[i];

    return 0;
}

int LD_Fx65(struct t_processor* processor, uint8_t x)
{
    if (x >= 16)
        return 1;

    for (unsigned int i = 0 ; i <= x ; i++)
         processor->generalRegister[i] = processor->RAM->ram[processor->IRegister+i];

    return 0;
}
