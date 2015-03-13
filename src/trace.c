/*
    file:   trace.c
    author: Dave Smith-Hayes
    date:   March 5th, 2015

    This file holds the trace() and fetch() functions.
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"

void
trace()
{
    fetch((void *) memory);
    
    fprintf(stdout, "MRA:\t0x%08lX\n", mar);
    fprintf(stdout, "MBR:\t0x%08lX\n", mbr);
    fprintf(stdout, "PC:\t0x%08lX\n", registers[PC]);
    fprintf(stdout, "IR0:\t0x%04X\n", ir0(ir));
    fprintf(stdout, "IR1:\t0x%04X\n", ir1(ir));

    return;
}
