/*
    Performs the immediate instruction passed to the function.
    Basically everything is done within the big ass switch statement.
    
    file:       immediate.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "registers.h"
#include "operations.h"

void
immediate(
        unsigned int mask,
        unsigned int inst,
        registers *reg)
{
    unsigned int rd = get_rd(inst);
    unsigned int imm = get_imm(inst);
    
    switch(mask) {
        case MOV_IMM:
            reg->file[rd] = (unsigned long) imm;

            break;


        case CMP_IMM:
            if((reg->file[rd] - imm) == 0)
                toggle_ccr(ZERO, &(reg->ccr));

            if((reg->file[rd] - imm) < 0)
                toggle_ccr(SIGN, &(reg->ccr));

            break;


        case ADD_IMM:
            reg->file[rd] += imm;
            
            break;


        case SUB_IMM:
            reg->file[rd] -= imm;

            if(reg->file[rd] < 0)
                set_ccr(SIGN, &(reg->ccr));
            
            break;
    }

    return;
}

unsigned int
get_imm(unsigned int inst)
{
    return (inst & IMM_VAL) / IMM_SHIFT;
}
