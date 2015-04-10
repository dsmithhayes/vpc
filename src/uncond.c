/*
    file:       uncond.c
    author:     Dave Smith-Hayes
    date:       March 31, 2015

    This function will do any type of unconditional branch.
*/

#include "registers.h"
#include "operations.h"

void
uncond(uint16_t inst, registers *reg)
{
    uint16_t addr = GET_UN_OFFSET(inst);
    
    /*
     * This is your regular unconditional branch.
     */
    if(IS_UN_BRA(inst))
        reg->file[PC] = (uint32_t) addr;
    /*
     * This is your unconditional branch with but
     * store the value of the link register
     */
    else if(IS_UN_BRL(inst)) {
        
    }
    
    return;
}
