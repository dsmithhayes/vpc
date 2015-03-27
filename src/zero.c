/*
    file:   zero.c
    author: Dave Smith-Hayes
    date:   February 27th, 2015
    
    this will take all of the registers and assign all their
    values to zero.
*/

#include <stdio.h>
#include "registers.h"

void
zero(registers *reg)
{
    int i;
    
    for(i = 0; i < REG_FILE_S; i++)
        reg->file[i] = 0;
    
    reg->ccr = 0;
    reg->mbr = 0;
    reg->mar = 0;
    reg->ir  = 0;
    reg->alu = 0;
    
    reg->stop_flag = 0;
    reg->ir_flag   = 0;
    
    return;
}
