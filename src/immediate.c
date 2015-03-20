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
                set_flg(ZERO, &(reg->ccr));

            if((reg->file[rd] - imm) < 0)
                set_flg(SIGN, &(reg->ccr));
        break;

        case ADD_IMM:
            reg->file[rd] += imm;

            if(reg->file[rd] == 0)
                set_flg(ZERO, &(reg->ccr));
        break;

        case SUB_IMM:
            reg->file[rd] -= imm;

            if(reg->file[rd] < 0)
                set_flg(SIGN, &(reg->ccr));

            if(reg->file[rd] == 0)
                set_flg(ZERO, &(reg->ccr));
        break;
    }

    /* toggle the instruction register flag */
    toggle_flg(INST, (unsigned long *) &(reg->ir_flg));

    return;
}

/*
 * Snags the immediate value out of the 2byte representing an
 * immediate operation.
 */
unsigned int
get_imm(unsigned int inst)
{
    return (inst & IMM_VAL) / IMM_SHIFT;
}
