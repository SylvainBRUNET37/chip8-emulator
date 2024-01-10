#include "ram.h"
#include "processor.h"

int main()
{
    uint8_t test2 = 240;
    uint8_t test = test2/100;
    printf("%d\n", test);
    printf("%d\n", test2);
    return 0;
}