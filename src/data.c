/*
    file:       data.c
    author:     Dave Smith-Hayes
    date:       March 28, 2015
    
    Performs a register to register operation.
*/

#include "registers.h"
#include "operations.h"


void
data(uint16_t inst, registers *reg)
{
    uint32_t i;
    
    uint8_t rd = RD(inst);
    uint8_t rn = RN(inst);
    uint16_t opcode = DAT_GET_OPCODE(inst);
    
    switch(opcode) {
    case AND_DAT:
        reg->alu = reg->file[rd] & reg->file[rn];
        sz(reg);
        reg->file[rd] = reg->alu;
        break;
    
    case EOR_DAT:
        reg->alu = reg->file[rd] ^ reg->file[rn];
        sz(reg);
        reg->file[rd] = reg->alu;
        break;
    
    case SUB_DAT:
        reg->alu = reg->file[rd] + ~reg->file[rn] + 1;
        scz(reg, rd, ~(rn + 1));
        reg->file[rd] = reg->alu;
        break;
    
    case SXB_DAT:
        reg->alu = (BYTE_MASK & reg->file[rn]);
        sz(reg);
        reg->file[rd] = reg->alu;
        break;
    
    case ADD_DAT:
        reg->alu = reg->file[rd] + reg->file[rn];
        scz(reg, rd, rn);
        reg->file[rd] = reg->alu;
        break;
    
    case ADC_DAT:
        reg->alu = reg->file[rd] 
                + reg->file[rn] 
                + IS_CARRY_SET(reg->ccr);
        scz(reg, rd, rn);
        reg->file[rd] = reg->alu;
        break;
    
    /*
     * Push all the bits save for the last one, check if will
     * be the carry, set the carry if it is, finish the shifting.
     */
    case LSR_DAT:
        reg->alu = reg->file[rd] >> (reg->file[rn] - 1);
        
        if(HAS_LSB(reg->alu))
            set_reg_flag(CARRY_FLAG, &(reg->ccr));
        
        reg->alu = (reg->alu >> 1);
        
        sz(reg);
        reg->file[rd] = reg->alu;
        break;
    
    /*
     * Same as above, other direction.
     */
    case LSL_DAT:
        reg->alu = reg->file[rd] << (reg->file[rn] - 1);
        
        if(HAS_MSB(reg->alu))
            set_reg_flag(CARRY_FLAG, &(reg->ccr));
        
        reg->alu = (reg->alu << 1);
        
        sz(reg);
        reg->file[rd] = reg->alu;
        break;

    case TST_DAT:
        reg->alu = reg->file[rd] & reg->file[rn];
        scz(reg, rd, rn);
        break;

    case TEQ_DAT:
        reg->alu = reg->file[rd] ^ reg->file[rn];
        scz(reg, rd, rn);
        break;

    case CMP_DAT:
        reg->alu = reg->file[rd] + ~reg->file[rn] + 1;
        scz(reg, rd, rn);
        break;

    /*
     * Rotate is weird because the LSB sets the carry and also 
     * becomes the MSB every shift.
     */
    case ROR_DAT:
        reg->alu = reg->file[rd];
        
        for(i = 0; i < reg->file[rn]; i++) {
            if(HAS_LSB(reg->alu))
                set_reg_flag(CARRY_FLAG, &(reg->ccr));
            
            reg->alu = (reg->alu >> 1);
            
            if(IS_CARRY_SET(reg->ccr))
                reg->alu |= MSB_MASK;
        }
        
        sz(reg);
        reg->file[rd] = reg->alu;
        break;

    case ORR_DAT:
        reg->alu = reg->file[rd] | reg->file[rn];
        sz(reg);
        reg->file[rd] = reg->alu;
        break;

    case MOV_DAT:
        reg->alu = reg->file[rn];
        sz(reg);
        reg->file[rd] = reg->alu;
        break;

    case BIC_DAT:
        reg->alu = ~(reg->file[rd] & reg->file[rd]);
        sz(reg);
        reg->file[rd] = reg->alu;
        break;

    case MVN_DAT:
        reg->alu = ~reg->file[rn];
        sz(reg);
        reg->file[rd] = reg->alu;
        break;
    }
    
    return;
}
