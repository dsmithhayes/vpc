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
    uint8_t rd   = get_rd(inst);
    uint8_t imm  = get_imm(inst);

    /*
     * Check which immediate instruction is given.
     */
    switch(buf) {
        case MOV_IMM:
            reg->alu (uint32_t) imm;
            reg->file[rd] = reg->alu;
            break;

        case CMP_IMM:
            reg->alu = reg->file[rd] & ~imm + 1;
            break;

        case ADD_IMM:
            reg->alu = reg->file[rd] + imm;
            reg->file[rd] = reg->alu;
            break;
    
        case SUB_IMM:
            reg->alu = reg->file[rd] & ~imm + 1;
            reg->file[rd] = reg->alu;
            break;
    }
    
    /*
     * Checks if the ZERO_FLAG should be set
     */
    if(IS_ZERO(reg->alu))
        set_reg_flag(ZERO_FLAG, &(reg->ccr));
    
    /*
     * Checks if the SIGN_FLAG should be set
     */
    if(IS_SIGN(reg->alu))
        set_reg_flag(SIGN_FLAG, &(reg->ccr));

    return;
}
