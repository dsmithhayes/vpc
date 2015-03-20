/*
    Functions in this file change the value of the flag that is
    passed to it.

    file:       flags.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "registers.h"
#include "operations.h"


/*
 * Returns non-zero if valid CCR mask
 */
uint8_t
is_mask(uint16_t mask) {
    if(mask == SIGN)
        return SIGN;

    if(mask == ZERO)
        return ZERO;

    if(mask == ((STOP | INST) | CARRY))
        return ((STOP | INST) | CARRY);

    return 0;
}


/*
 * Only toggles valid flag mask passed.
 */
void
toggle_flg(uint16_t mask, uint32_t *ctrl_reg)
{
    if(is_mask(mask))
        *ctrl_reg = ((*ctrl_reg & mask) == mask)
                ? (*ctrl_reg & ~mask)       /* remove the flag  */
                : (*ctrl_reg | mask);       /* add the flag     */
    
    return;
}

/*
 * Always sets the flag given.
 */
void
set_flg(uint16_t mask, uint32_t *ctrl_reg)
{
    if(is_mask(mask))
        *ctrl_reg |= mask;

    return;
}

/*
 * Always set the flag to zero. To make sure it doesn't become
 * negative or something weird, just make sure it is on and toggle
 * it off, or just keep it off.
 */
void
clear_flg(uint16_t mask, uint32_t *ctrl_reg)
{
    if(is_mask(mask))
        *ctrl_reg = (*ctrl_reg & mask)
                ? (*ctrl_reg - mask) : *ctrl_reg;

    return;
}
