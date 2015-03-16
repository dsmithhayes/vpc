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
trace(void *memory, struct registers *reg)
{
    char in;

    fprintf(stdout, "Any button to trace, period to exit.\n");

    fprintf(stdout, "0x%08lX> ", reg->file[PC]);
    while((in = getchar()) != '.') {
        /* Basically just single step through the program */
        fetch(memory, reg);

        dumpreg(*reg);
        fprintf(stdout, "0x%08lX> ", reg->file[PC]);
    }

    return;
}
