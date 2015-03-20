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
    /*
     * Obvious variable declarations, just read it.
     */
    unsigned int rd  = get_rd(inst);
    unsigned int imm = get_imm(inst);

    /*
     * Begin!
     */
    switch(mask) {
        /*
         * Move immediate value into the register.
         */
        case MOV_IMM:
            reg->file[rd] = (unsigned long) imm;
        break;

        /*
         * Compare the immediate value to the one in the register,
         * set the flag accordingly.
         */
        case CMP_IMM:
            if((reg->file[rd] - imm) == 0)
                set_flg(ZERO, &(reg->ccr));

            if((reg->file[rd] - imm) < 0)
                set_flg(SIGN, &(reg->ccr));
        break;

        /*
         * Add the immediate value into the register.
         */
        case ADD_IMM:
            reg->file[rd] += imm;

            if(reg->file[rd] == 0)
                set_flg(ZERO, &(reg->ccr));
        break;

        /*
         * Substract the imemdiate value from the value in the
         * register.
         */
        case SUB_IMM:
            reg->file[rd] -= imm;

            if(reg->file[rd] < 0)
                set_flg(SIGN, &(reg->ccr));

            if(reg->file[rd] == 0)
                set_flg(ZERO, &(reg->ccr));
        break;
    }

    /*
     * toggle the instruction register flag
     */
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
