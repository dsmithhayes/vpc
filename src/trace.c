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
#include "operations.h"

void
trace(void *memory, registers *reg)
{
    char in;

    fprintf(stdout, "\nPress any button to trace, '.' to exit.\n");

    fprintf(stdout, "0x%08X> ", reg->file[PC]);

    while((in = getchar()) != '.') {
        fetch(memory, reg);

        if(reg->ir_flag)
            execute(IR1(reg->ir), reg, memory);
        else
            execute(IR0(reg->ir), reg, memory);

        dumpreg(*reg);

        fprintf(stdout, "\n0x%08X> ", reg->file[PC]);
    }

    return;
}
