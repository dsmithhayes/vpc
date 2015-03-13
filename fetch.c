/*
    Fetches the next instruction from the memory. 

    file:       fetch.c
    author:     Dave Smith-Hayes
    date:       Mar 12, 2015
*/

#include "vpc.h"

void
fetch()
{
    mar = registers[PC];
}
