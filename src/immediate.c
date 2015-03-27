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

    switch(buf) {
        case MOV_IMM:
            reg->file[rd] = (uint32_t) imm;
        break;

        case CMP_IMM:
            if(IS_ZERO(reg->file[rd] & (~imm + 1)))
                set_reg_flg(ZERO_FLAG, &(reg->ccr));
    
            if(IS_SIGN(reg->file[rd] & (~imm + 1)))
                set_reg_flg(SIGN_FLAG, &(reg->ccr));
        break;
    
        case ADD_IMM:
            reg->file[rd] += imm;
    
            if(IS_ZERO(reg->file[rd]))
                set_flag(ZERO_FLAG, &(reg->ccr));

            if(IS_CARRY(reg->file[rd]))
                set_flag(CARRY_FLAG, &(reg->ccr));

        break;
    
        case SUB_IMM:
            reg->file[rd] &= ~imm++;
    
            if(IS_SIGN(reg->file[rd]))
                set_flag(SIGN_FLAG, &(reg->ccr));
    
            if(IS_ZERO(reg->file[rd]))
                set_flag(ZERO_FLAG, &(reg->ccr));
        break;
    }

    toggle_flg(INST_FLAG, &(reg->ir));

    return;
}
