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
    uint8_t rd = get_rd(inst);
    uint8_t rn = get_rn(inst);
    uint8_t opcode = DAT_GET_OPCODE(inst);
    
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

        case TST_AT:

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
            
            break;

        case BIC_DAT:

            break;

        case MVN_DAT:

            break;
    }
    reg->file[rd] = reg->alu;
    
    toggle_reg_flag(INST_FLAG, &(reg->ccr));
    
    return;
}
