/*
    Fetches the next instruction from the memory. 

    file:       fetch.c
    author:     Dave Smith-Hayes
    date:       Mar 12, 2015
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"

/* HA! I used it! */
#define BITS_PER_BYTE   8;


void
fetch(void *memory)
{
    int i = 0;
    unsigned long buffer;
    
    mar = registers[PC];
    registers[PC] += REG_SIZE;

    do {
        mbr << BITS_PER_BYTE;
        buffer = *((char *) memory + (mar + (i++)));

        mbr += buffer;
    } while (i != REG_SIZE);

    ir = mbr;
}
