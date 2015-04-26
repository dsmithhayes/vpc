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
    char in, _exit = '.';

    fprintf(stdout, "Press enter/return to trace, '%c' to exit.\n", _exit);

    /*
     * The cursor for the trace displays the Program Counter
     */
    fprintf(stdout, "0x%08X> ", reg->file[PC]);

    /*
     * Fetch the memory, execute the instruction according to the instruction
     * register set, dump the register after each instruction is performed.
     */
    while((in = getchar()) != _exit) {
        fetch(memory, reg);

        execute(IR0(reg->ir), reg, memory);
        dumpreg(*reg);

        fprintf(stdout, "\n0x%08X> ", (reg->file[PC] - INSTR_SIZE));

        if((in = getchar()) == _exit)
            return;
        
        execute(IR1(reg->ir), reg, memory);
        dumpreg(*reg);

        fprintf(stdout, "\n0x%08X> ", reg->file[PC]);
    }

    return;
}
