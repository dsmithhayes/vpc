/*
    All of the routines here correspond with the precessor operation.

    file:       operations.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "operations.h"
#include "registers.h"

uint8_t
is_inst(uint16_t mask, uint16_t inst)
{
    return ((mask & inst) == mask) ? 1 : 0;
}

uint8_t
get_rd(uint16_t val)
{
    return (val & RD_MASK);
}

uint8_t
get_rn(uint16_t val)
{
    return (val & RN_MASK) >> RN_SHIFT;
}
