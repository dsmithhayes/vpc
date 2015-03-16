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
fetch(void *memory, struct registers *reg)
{
    int i;

    reg->mbr = 0;

    reg->mar = reg->file[PC];
    reg->file[PC] += REG_SIZE;

    /* grab the next 4 bytes of memory into the mbr */
    for(i = 0; i < REG_SIZE; i++) {
        reg->mbr +=
                (unsigned long) *((char *) memory + (reg->mar + i));

        if(i != (REG_SIZE - 1))
            reg->mbr = reg->mbr << BITS_PER_BYTE;
    }

    reg->ir = reg->mbr;
    
    return;
}