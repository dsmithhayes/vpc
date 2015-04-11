/*
    file:       uncond.c
    author:     Dave Smith-Hayes
    date:       March 31, 2015

    This function will do any type of unconditional branch.
*/

#include "registers.h"
#include "operations.h"

void
uncond(uint16_t inst, registers *reg, void *memory)
{
    uint16_t addr = GET_UN_OFFSET(inst);    /* 12bit offset */

    /*
     * set the address buffer to targer the appropriate memory
     */
    reg->mar = addr;
    
    /*
     * This is your regular unconditional branch.
     */
    if(IS_UN_BRA(inst)) {
        reg->file[PC] = (uint32_t) addr;
        
        return;
    }
    
    /*
     * This is your unconditional branch with but
     * store the value of the link register
     */
    if(IS_UN_BRL(inst)) {
        push(reg->file[LR], &(reg->mar), memory);
        reg->file[PC] = (uint32_t) addr;
        
        return;
    }
    
    return;
}
