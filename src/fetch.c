/*
    Fetches the next instruction from the memory. 

    file:       fetch.c
    author:     Dave Smith-Hayes
    date:       Mar 12, 2015
*/

#include <stdio.h>
#include "registers.h"

void
fetch(void *memory)
{
    mar = registers[PC];
}
