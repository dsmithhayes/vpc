/*
    Executes the instruction given. First it decides which instruction
    it is, and then proceeds to perform the operation to the according
    registers within the opcode data.

    there is an `immediate()` and `data()` function that will perform
    the appropriate operation based on the positive mask match.
    
    file:       execute.c
    author:     Dave Smith-Hayes
    date:       March 17, 2015
*/

#include "registers.h"
#include "operations.h"


void
execute(uint16_t inst, registers *reg)
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
        toggle_flg(STOP, (uint32_t *) &(reg->stp_flg));
    
    return;
}
