#include "instructions.h"

int clearDisplay_00E0(struct t_processor* processor)
{
    return 0;
}

int setPCtoTopStack_00EE(struct t_processor* processor)
{
    processor->programCounter = processor->stack[processor->stackPointer];
    processor->stackPointer--;
    return 0;
}

int jumpTo_1nnn(struct t_processor* processor, uint16_t nnn)
{
    processor->programCounter = nnn;
    return 0;
}

int putPCtoTopStack_2nnn(struct t_processor* processor, uint16_t nnn)
{
    processor->stackPointer++;
    processor->stack[processor->stackPointer] = processor->programCounter;
    processor->programCounter = nnn;
}

int skipIfXequalKK_3xkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x > 16)
        return 1;
    if (processor->generalRegister[x] == kk)
        processor->programCounter++;
    return 0;
}

int skipIfXnotEqualKK_4xkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x > 16)
        return 1;
    if (processor->generalRegister[x] != kk)
        processor->programCounter++;
    return 0;
}

int skipIfXequalY_5xy0(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    if (processor->generalRegister[x] != processor->generalRegister[y])
        processor->programCounter++;
    return 0;
}

int setXtoKK_6xkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x > 16)
        return 1;
    processor->generalRegister[x] = kk;
    return 0;
}

int addXandKK_7xkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x > 16)
        return 1;
    processor->generalRegister[x] += kk;
    return 0;
}

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

int div2operation_8xy6(struct t_processor* processor, uint8_t x)
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
    if (processor->generalRegister[y] > processor->generalRegister[x])
    {
        processor->generalRegister[15] = 1;
    }
    processor->generalRegister[x] = processor->generalRegister[y] - processor->generalRegister[x];
    return 0;
}

int mul2operation_8xyE(struct t_processor* processor, uint8_t x)
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

int skipNextinstruction_9xy0(struct t_processor* processor, uint8_t x, uint8_t y)
{
    if (x > 16 || y > 16)
        return 1;
    if (processor->generalRegister[x] != processor->generalRegister[y])
        processor->programCounter += 2;
    return 0;
}

int setIvalue_Annn(struct t_processor* processor, uint16_t nnn)
{
    processor->IRegister = nnn;
    return 0;
}

int jumpTo_Bnnn(struct t_processor* processor, uint16_t nnn)
{
    processor->programCounter = nnn + processor->generalRegister[0];
    return 0;
}

int setRandom_Cxkk(struct t_processor* processor, uint8_t x, uint8_t kk)
{
    if (x > 16)
        return 1;
    uint8_t temp = rand();
    processor->generalRegister[x] = temp & kk;
    return 0;
}

int displaySprite_Dxyn(struct t_processor* processor, uint8_t x, uint8_t y, uint8_t n)
{
    if (x > 16 || y > 16 || n > 16)
        return 1;
    return 0;
}

int jumpIfKeyPressed_Ex9E(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    return 0;
}

int jumpIfKeyNotPressed_ExA1(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    return 0;
}

int setXtoDL_Fx07(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    processor->generalRegister[x] = processor->delayTimerRegister;
    return 0;
}

int waitKeyPressed(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    return 0;
}

int setDTtoX_Fx18(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    processor->delayTimerRegister = processor->generalRegister[x];
    return 0;
}

int setSTtoX_Fx15(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    processor->soundTimerRegister = processor->generalRegister[x];
    return 0;
}

int addIandX_Fx1E(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    processor->IRegister += processor->generalRegister[x];
    return 0;
}

int setItoSpriteX_Fx29(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;
    processor->IRegister = processor->generalRegister[x];
    return 0;
}

int setXtoI_Fx33(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;

    uint8_t temp = processor->generalRegister[x];

    processor->RAM->ram[processor->IRegister] = temp / 100;
    temp %= 100;
    processor->RAM->ram[processor->IRegister+1] = temp / 10;
    temp %= 10;
    processor->RAM->ram[processor->IRegister+2] = temp;
    return 0; 
}

int storeRegisterInMemory_Fx55(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;

    for (unsigned int i = 0 ; i < x ; i++)
        processor->RAM->ram[processor->IRegister+i] = processor->generalRegister[i];

    return 0;
}

int readMemory_Fx65(struct t_processor* processor, uint8_t x)
{
    if (x > 16)
        return 1;

    for (unsigned int i = 0 ; i < x ; i++)
         processor->generalRegister[i] = processor->RAM->ram[processor->IRegister+i];

    return 0;
}
