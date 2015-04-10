/*
    file:       fetch.c
    author:     Dave Smith-Hayes
    date:       Mar 12, 2015
    
    Fetches the next instruction from the memory.
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"


void
fetch(void *memory, registers *reg)
{
    reg->mar = reg->file[PC];
    reg->file[PC] += REG_SIZE;

    /*
     * grab the next 4 bytes of memory into the mbr
     */
    reg->mbr += *((uint8_t *) memory + (reg->mar++));
    reg->mbr = (reg->mbr << BYTE);

    reg->mbr += *((uint8_t *) memory + (reg->mar++));
    reg->mbr = (reg->mbr << BYTE);

    reg->mbr += *((uint8_t *) memory + (reg->mar++));
    reg->mbr = (reg->mbr << BYTE);

    reg->mbr += *((uint8_t *) memory + (reg->mar++));
    
    /*
     * Set the instruction register to the result of MBR
     */
    reg->ir = reg->mbr;
    return;
}
