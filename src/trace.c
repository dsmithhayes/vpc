/*
    file:   trace.c
    author: Dave Smith-Hayes
    date:   March 5th, 2015

    Tracing the program is single stepping through the program counter
    and veiwing the register set after each instruction.
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"

void
trace(void *memory, registers *reg)
{
    char in;

    fprintf(stdout, "Any button to trace, period to exit.\n");

    fprintf(stdout, "0x%08X> ", reg->file[PC]);

    while((in = getchar()) != '.') {
        fetch(memory, reg);
        dumpreg(*reg);

        fprintf(stdout, "\n0x%08X> ", reg->file[PC]);
    }

    return;
}
