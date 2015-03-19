/*
    Functions in this file change the value of the flag that is
    passed to it.

    file:       flags.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "operations.h"

void
set_flg(unsigned short *flag)
{
    *flag = !*flag;
    return;
}

void
set_ccr(unsigned int mask, unsigned long *cntrl_reg)
{
    switch(mask) {
        case ZERO:
            *cntrl_reg |= ZERO;
            break;
        case CARRY:
            *cntrl_reg |= CARRY;
            break;
        case SIGN:
            *cntrl_reg |= SIGN;
            break;
    }

    return;
}
