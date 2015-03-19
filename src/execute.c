/*
    Executes the instruction given
    
    file:       execute.c
    author:     Dave Smith-Hayes
    date:       March 17, 2015
*/

#include "registers.h"
#include "operations.h"

void
execute(unsigned int inst, registers *reg)
{
    if(inst & MOV_IMM) {
        
    }
        
    return;
}


unsigned int
get_rd(unsigned int val)
{
    return val & RD_MASK;
}

unsigned int
get_rn(unsigned int val)
{
    return val & RN_MASK;
}
