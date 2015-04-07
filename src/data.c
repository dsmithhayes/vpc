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
            sz(reg->alu, &(reg->ccr));
            reg->file[rd] = reg->alu;
            break;
        
        case EOR_DAT:
            reg->alu = reg->file[rd] ^ reg->file[rn];
            sz(reg->alu, &(reg->ccr));
            reg->file[rd] = reg->alu;
            break;
        
        case SUB_DAT:
            reg->alu = reg->file[rd] + ~reg->file[rn] + 1;
            scz(reg->alu, rd, rn, &(reg->ccr));
            reg->file[rd] = reg->alu;
            break;
        
        case SXB_DAT:
            
            break;
        
        case ADD_DAT:
            reg->alu = reg->file[rd] + reg->file[rn];
            scz(reg->alu, rd, rn, &(reg->ccr));
            reg->file[rd] = reg->alu;
            break;
        
        case ADC_DAT:
            reg->alu = reg->file[rd] 
                    + reg->file[rn] 
                    + IS_CARRY_SET(reg->ccr);
            
            scz(reg->alu, rd, rn, &(reg->ccr));
            
            reg->file[rd] = reg->alu;
            break;
        
        case LSR_DAT:
            reg->alu = reg->file[rd] >> reg->file[rn];
            scz(reg->alu, rd, rn, &(reg->ccr));
            
            reg->file[rd] = reg->alu;
            break;
        
        case LSL_DAT:
            reg->alu = reg->file[rd] << reg->file[rn];
            scz(reg->alu, rd, rn, &(reg->ccr));
            
            reg->file[rd] = reg->alu;
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
