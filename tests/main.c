#include <stdio.h>
#include "ramFunction.h"

int main()
{
    struct t_RAM* RAM = newRAM();
    printf("Code erreur write : %d\n", writeRAM(RAM, 0, 44));

    printf("Valeur lu dans la RAM : %d\n", readRAM(RAM, 0));
    deleteRAM(RAM);
    return 0;
}