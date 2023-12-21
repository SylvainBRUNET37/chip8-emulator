#include "instructions.h"

int setOperation_8xy0(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 15 || y > 15)
        return 1;
    processor->generalRegister[x] = processor->generalRegister[y];
    return 0;
}

int orOperation_8xy1(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 15 || y > 15)
        return 1;
    processor->generalRegister[x] = ((processor->generalRegister[x]) | (processor->generalRegister[y]));
    return 0;
}

int andOperation_8xy2(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 15 || y > 15)
        return 1;
    processor->generalRegister[x] = ((processor->generalRegister[x]) & (processor->generalRegister[y]));
    return 0;
}

int exclusifOrOperation_8xy3(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 15 || y > 15)
        return 1;
    processor->generalRegister[x] = ((processor->generalRegister[x]) ^ (processor->generalRegister[y]));
    return 0;
}

// pas sure que ça marche
int addOperation_8xy4(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 15 || y > 15)
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