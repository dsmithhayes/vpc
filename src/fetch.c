/*
    file:       fetch.c
    author:     Dave Smith-Hayes
    date:       Mar 12, 2015
    
    Fetches the next instruction from the memory.
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"
#include "operations.h"


void
fetch(void *memory, registers *reg)
{
    reg->mar = reg->file[PC];
    reg->file[PC] += REG_SIZE;

    /*
     * Get the bytes out of memory.
     */
    pull(&(reg->mbr), &(reg->mar), memory);
    
    /*
     * Set the instruction register to the result of MBR
     */
    reg->ir = reg->mbr;
    return;
}
