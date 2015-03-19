/*
    All of the routines here correspond with the precessor operation.

    file:       operations.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "operations.h"
#include "registers.h"

unsigned short
is_inst(unsigned int mask, unsigned int inst)
{
    return (mask & inst) ? 1 : 0;
}
