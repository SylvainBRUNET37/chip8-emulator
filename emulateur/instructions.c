#include "instructions.h"

int setOperation_8xy0(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    processor->generalRegister[x] = processor->generalRegister[y];
    return 0;
}

int orOperation_8xy1(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    processor->generalRegister[x] = ((processor->generalRegister[x]) | (processor->generalRegister[y]));
    return 0;
}

int andOperation_8xy2(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    processor->generalRegister[x] = ((processor->generalRegister[x]) & (processor->generalRegister[y]));
    return 0;
}

int exclusifOrOperation_8xy3(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    processor->generalRegister[x] = ((processor->generalRegister[x]) ^ (processor->generalRegister[y]));
    return 0;
}

// pas sure que ça marche
int addOperation_8xy4(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    uint16_t temp = x + y;
    if (temp > 255)
    {
        temp = (temp & 255);
        processor->generalRegister[15] = 1;
    }
    processor->generalRegister[x] = temp;
    return 0;
}

int subOperation_8xy5(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    // Si Vx est supérieur à Vy, met VF à 1
    if (processor->generalRegister[x] > processor->generalRegister[y])
    {
        processor->generalRegister[15] = 1;
    }
    processor->generalRegister[x] -= processor->generalRegister[y];
    return 0;
}

int div2Operation_8xy6(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    // Si le bit de poid le plus faible de Vx est égale à 1, met le reste dans VF
    if ((processor->generalRegister[x] & 1) == 1)
    {
        processor->generalRegister[15] = 1;
    }
    processor->generalRegister[x] /= 2;
    return 0;
}

int subnOperation_8xy7(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    // Si Vy est supérieur à Vx, met VF à 1
    if (processor->generalRegister[y] > processor->generalRegister[yx])
    {
        processor->generalRegister[15] = 1;
    }
    processor->generalRegister[x] = processor->generalRegister[y] - processor->generalRegister[x];
    return 0;
}

int mul2Operation_8xyE(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    // Si le bit de poid le plus fort de Vx est égale à 1, met le reste dans VF
    if ((processor->generalRegister[x] & 128) == 1)
    {
        processor->generalRegister[15] = 1;
    }
    processor->generalRegister[x] *= 2;
    return 0;
}