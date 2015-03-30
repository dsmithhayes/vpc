/*
    Executes the instruction given. First it decides which instruction
    it is, and then proceeds to perform the operation to the according
    registers within the opcode data.

    there is an `immediate()` and `data()` function that will perform
    the appropriate operation based on the positive mask match.
    
    file:       execute.c
    author:     Dave Smith-Hayes
    date:       March 26, 2015
*/

#include "registers.h"
#include "operations.h"

/*
 * THERE'S AN EASIER WAY TO DO THIS
 *
 * THERE DOESN'T SEEM TO BE AN EASIER WAY TO DO THIS JEEEEEEZ
 */

void
execute(uint16_t inst, registers *reg)
{
    /*
     * TEST THE TYPE OF INSTRUCTION IN EXECUTE, PERFORM THE
     * APPROPRIATE FUNCTION
     */

    if(IS_IMM_INST(inst)) {
        immediate(inst, reg);
        return;
    }
    
    if(IS_DAT_INST(inst)) {
        data(inst, reg);
        return;
    }

    toggle_reg_flag(INST_FLAG, &(reg->ir_flag));
    
    return;
}
