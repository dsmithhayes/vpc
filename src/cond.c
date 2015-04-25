/*
    file:       cond.c
    author:     Dave Smith-Hayes
    date:       March 31, 2015
    
    This is where all of the conditional branches are executed.
*/

#include "registers.h"
#include "operations.h"

void
cond(uint16_t inst, registers *reg)
{
    int8_t addr = COND_GET_ADDR(inst);  /* always a signed value */
    
    switch(COND_GET_OPCODE(inst)) {
    /*
     * ignores all conditions
     */
    case COND_AL:
        reg->file[PC] += addr;
        break;
    
    /*
     * zero set
     */
    case COND_EQ:
        if(IS_ZERO_SET(reg->ccr))
            reg->file[PC] += addr;
        
        break;
    
    /*
     * zero clear
     */
    case COND_NE:
        if(!IS_ZERO_SET(reg->ccr))
            reg->file[PC] += addr;
        
        break;
    
    /*
     * carry set
     */
    case COND_CS:
        if(IS_CARRY_SET(reg->ccr))
            reg->file[PC] += addr;
        
        break;
    
    /*
     * carry clear
     */
    case COND_CC:
        if(!IS_CARRY_SET(reg->ccr))
            reg->file[PC] += addr;
    
        break;
    
    /*
     * sign set
     */
    case COND_MI:
        if(IS_SIGN_SET(reg->ccr))
            reg->file[PC] += addr;
    
        break;
    
    /*
     * sign clear
     */
    case COND_PL:
        if(!IS_SIGN_SET(reg->ccr))
            reg->file[PC] += addr;

        break;
    
    /*
     * carry set
     * sign clear
     */
    case COND_HI:
        if(IS_CARRY_SET(reg->ccr)
                && !IS_SIGN_SET(reg->ccr))
            reg->file[PC] += addr;
        
        break;
    
    /*
     * carry set,
     * sign clear
     */
    case COND_LS:
        if(IS_SIGN_SET(reg->ccr)
                && !IS_CARRY_SET(reg->ccr))
            reg->file[PC] += addr;
            
        break;
    }
    
    return;
}
