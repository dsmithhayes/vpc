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
#define BITS_PER_BYTE   8


void
fetch(void *memory, registers *reg)
{
    reg->mbr = 0;

    reg->mar = reg->file[PC];
    reg->file[PC] += REG_SIZE;

    /*
     * grab the next 4 bytes of memory into the mbr
     */
    reg->mbr += *((uint8_t *) memory + (reg->mar++));
    reg->mbr = (reg->mbr << BITS_PER_BYTE);

    reg->mbr += *((uint8_t *) memory + (reg->mar++));
    reg->mbr = (reg->mbr << BITS_PER_BYTE);

    reg->mbr += *((uint8_t *) memory + (reg->mar++));
    reg->mbr = (reg->mbr << BITS_PER_BYTE);

    reg->mbr += *((uint8_t *) memory + (reg->mar++));
    
    /*
     * Set the instruction register to the result of MBR
     */
    reg->ir = reg->mbr;
    return;
}
