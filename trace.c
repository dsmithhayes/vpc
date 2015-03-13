/*
    file:   trace.c
    author: Dave Smith-Hayes
    date:   March 5th, 2015

    This file holds the trace() and fetch() functions.
*/

#include "vpc.h"

void
trace()
{    
    fprintf(stdout, "MRA:\t0x%08lX\n", mra);
    fprintf(stdout, "MBR:\t0x%08lX\n", mbr);
    fprintf(stdout, "PC:\t0x%08lX\n", registers[PC]);
    fprintf(stdout, "IR0:\t0x%04X\n", ir0(ir));
    fprintf(stdout, "IR1:\t0x%04X\n", ir1(ir));
        
    return;
}
