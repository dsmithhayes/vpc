/*
    file:   zero.c
    author: Dave Smith-Hayes
    date:   February 27th, 2015
    
    this will take all of the registers and assign all their
    values to zero.
*/

#include "vpc.h"

void
zero()
{
    unsigned int i;
    
    for(i = 0; i < TOTAL_REG; i++)
        registers[i] = 0;
    
    ccr = 0;
    mbr = 0;
    mar = 0;
    ir  = 0;
    
    ir_flag = 0;
    stop_flag = 0;
    
    return;
}
