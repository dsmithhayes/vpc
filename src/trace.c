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
trace(struct registers *reg)
{
    char in;

    fprintf(stdout, "Any button to trace, period to exit.\n");

    fprintf(stdout, "0x%08lX> ", registers[PC]);
    while((in = getchar()) != '.') {
        /* Basically just single step through the program */
        fetch((void *) memory);

        fprintf(stdout, "0x%08lX> ", registers[PC]);
    }

    return;
}
