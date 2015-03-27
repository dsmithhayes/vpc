/*
    Performs the immediate instruction passed to the function.
    Basically everything is done within the big ass switch statement.
    
    file:       immediate.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "registers.h"
#include "operations.h"

/*
 * Monolithic function that performs the necessary immediate operation
 * to the data in register Rd.
 */
void
immediate(uint16_t inst, registers *reg)
{
    uint16_t buf = (inst & IMM_OPCODE);
    uint8_t  rd  = get_rd(inst);

    switch(buf) {
        case MOV_IMM:
            /*
             * code for move immediate
             */
        break;

        case CMP_IMM:
            /*
             * code for compare immediate
             */
        break;

        case ADD_IMM:
            /*
             * code for add immediate
             */
        break;

        case SUB_IMM:
            /*
             * code for substract immediate
             */
        break;
    }

    toggle_flg(INST_FLAG, &(reg->ir));

    return;
}
