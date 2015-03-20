/*
    Functions in this file change the value of the flag that is
    passed to it.

    file:       flags.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "registers.h"
#include "operations.h"


/* Returns non-zero if valid CCR mask */
inline short
is_ccr_mask(unsigned int mask) {
    if(mask == ZERO)
        return ZERO;

    if(mask == CARRY)
        return CARRY;

    if(mask == SIGN)
        return SIGN;

    return 0;
}

/* toggles the stop or instruction flags */
void
set_flg(unsigned short *flag)
{
    *flag = !*flag;
    return;
}

/* Only toggles valid CCR masks passed. */
void
toggle_ccr(unsigned int mask, unsigned long *ctrl_reg)
{
    if(is_ccr_mask(mask))
        *ctrl_reg = (*ctrl_reg & mask)
                ? (*ctrl_reg - mask)        /* remove the flag  */
                : (*ctrl_reg | mask);       /* add the flag     */
    
    return;
}

void
set_ccr(unsigned int mask, unsigned long *ctrl_reg)
{
    if(is_ccr_mask(mask))
        *ctrl_reg |= mask;

    return;
}

void
clear_ccr(unsigned int mask, unsigned long *ctrl_reg)
{
    if(is_ccr_mask(mask))
        *ctrl_reg -= mask;

    return;
}
