#include "./include/ram.h"
#include "./include/processor.h"

int main()
{
    uint16_t IRegister = 0;
    uint8_t x = 144; 
    
    IRegister += x / 100;
    x = x % 100;
    IRegister >> 4;

    IRegister += x / 10;
    x = x % 10;
    IRegister >> 4;

    IRegister += x;

    printf("%d\n", IRegister);
    return 0;
}
