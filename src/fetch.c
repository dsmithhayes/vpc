/*
    Fetches the next instruction from the memory. 

    file:       fetch.c
    author:     Dave Smith-Hayes
    date:       Mar 12, 2015
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"

#define BITS_PER_BYTE   8;


void
fetch(void *memory)
{
    int i = 0;
    
    mar = registers[PC];
    registers[PC] += REG_SIZE;

    do {
        mbr += mbr << BITS_PER_BYTE;            /* HA! I used it! */
        mbr = ((char *) memory + (mar + i++));
    } while (i != REG_SIZE);
}
