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
    
    return;
}

/*
 * Sets all the register flags for everything accordingly.
 *
 * sign
 * zero
 * carry
 */
static inline void
scz(uint32_t  alu,
    uint8_t   rd,
    uint8_t   rn,
    uint32_t *ccr)
{
    if(IS_SIGN(alu))
        set_reg_flag(SIGN_FLAG, ccr);
    else
        clear_reg_flag(SIGN_FLAG, ccr);

    if(is_carry(rd, rn, IS_CARRY_SET(*ccr)))
        set_reg_flag(CARRY_FLAG, ccr);
    else
        clear_reg_flag(CARRY_FLAG, ccr);

    if(IS_ZERO(alu))
        clear_reg_flag(ZERO_FLAG, ccr);
    else
        clear_reg_flag(ZERO_FLAG, ccr);

    return;
}

static inline void
sz(uint32_t alu, uint32_t *ccr)
{
    if(IS_SIGN(alu))
        set_reg_flag(SIGN_FLAG, ccr);
    else
        clear_reg_flag(SIGN_FLAG, ccr);

    if(IS_ZERO(alu))
        clear_reg_flag(ZERO_FLAG, ccr);
    else
        clear_reg_flag(ZERO_FLAG, ccr);
}
