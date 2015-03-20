/*
    Executes the instruction given
    
    file:       execute.c
    author:     Dave Smith-Hayes
    date:       March 17, 2015
*/

#include "registers.h"
#include "operations.h"


void
execute(unsigned int inst, registers *reg)
{
    /**************************/
    /* Immediate Instructions */
    /**************************/

    /* Move immediate value into Rd */
    if(is_inst(MOV_IMM, inst)) {
        immediate(MOV_IMM, inst, reg);
        return;
    }

    /* Compare immediate value to Rd */
    if(is_inst(CMP_IMM, inst)) {
        immediate(CMP_IMM, inst, reg);
        return;
    }

    /* Add immediate value into Rd */
    if(is_inst(ADD_IMM, inst)) {
        immediate(ADD_IMM, inst, reg);
        return;
    }

    /* Subtract immediate value from Rd */
    if(is_inst(SUB_IMM, inst)) {
        immediate(SUB_IMM, inst, reg);
        return;
    }


    /*********************/
    /* Data Instructions */
    /*********************/


    /**************/
    /* Stop flags */
    /**************/

    if(is_inst(STOP_INST, inst))
        toggle_flg(STOP, &(reg->stp_flg));
    
    return;
}


unsigned int
get_rd(unsigned int val)
{
    return val & RD_MASK;
}

unsigned int
get_rn(unsigned int val)
{
    return (val & RN_MASK) / IMM_SHIFT;
}
