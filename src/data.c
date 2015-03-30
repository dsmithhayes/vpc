/*
    Performs a register to register operation.
    
    file:       data.c
    author:     Dave Smith-Hayes
    date:       March 28, 2015
*/

#include "registers.h"
#include "operations.h"

void
data(uint16_t inst, registers *reg)
{
    uint8_t rd = RD(inst);
    uint8_t rn = RN(inst);
    uint16_t opcode = DAT_GET_OPCODE(inst);

    uint32_t _buf;
    
    switch(opcode) {
        case AND_DAT:
            reg->alu = reg->file[rd] & reg->file[rn];
            break;
        
        case EOR_DAT:
            reg->alu = reg->file[rd] ^ reg->file[rn];
            break;
        
        case SUB_DAT:
            reg->alu = reg->file[rd] - reg->file[rn];
            break;
        
        case SXB_DAT:
        
            break;
        
        case ADD_DAT:
            reg->alu = reg->file[rd] + reg->file[rn];
            break;
        
        case ADC_DAT:
            
            break;
        
        case LSR_DAT:
            reg->alu = reg->file[rd] >> reg->file[rn];
            break;
        
        case LSL_DAT:
            reg->alu = reg->file[rd] << reg->file[rn];
            break;

        case TST_DAT:

            break;

        case TEQ_DAT:

            break;

        case CMP_DAT:
            _buf = reg->file[rd] - reg->file[rn];

            if(IS_ZERO(_buf))
                set_reg_flag(ZERO_FLAG, &(reg->ccr));

            if(IS_SIGN(_buf))
                set_reg_flag(SIGN_FLAG, &(reg->ccr));

            if(is_carry(
                    reg->file[rd],
                    reg->file[rn],
                    IS_CARRY_SET(reg->ccr)))
                set_reg_flag(CARRY_FLAG, &(reg->ccr));
            break;

        case ROR_DAT:

            break;

        case ORR_DAT:
            reg->alu = reg->file[rd] | reg->file[rn];
            break;

        case MOV_DAT:
            reg->alu = reg->file[rn];
            reg->file[rd] = reg->alu;
            break;

        case BIC_DAT:

            break;

        case MVN_DAT:

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
