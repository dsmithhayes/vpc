/*
    file:       flags.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
    
    Functions in this file change the value of the flag that is
    passed to it.
*/

#include "registers.h"
#include "operations.h"


/*
 * Returns non-zero if valid CCR mask
 */
uint8_t
is_reg_mask(uint16_t mask) {
    if(mask == SIGN_FLAG)
        return SIGN_FLAG;

    if(mask == ZERO_FLAG)
        return ZERO_FLAG;

    /*
     * This is the most unecessary code I have ever written in my
     * life and I am ashamed and apalled to even look at it. Each
     * constant is equal to 1. I shit you not.
     */
    if(mask == ((STOP_FLAG | INST_FLAG) | CARRY_FLAG))
        return ((STOP_FLAG | INST_FLAG) | CARRY_FLAG);

    return 0;
}


/*
 * Only toggles valid flag mask passed.
 */
void
toggle_reg_flag(uint16_t mask, uint32_t *ctrl_reg)
{
    if(is_reg_mask(mask))
        *ctrl_reg = ((*ctrl_reg & mask) == mask)
                ? (*ctrl_reg & ~mask)       /* remove the flag  */
                : (*ctrl_reg | mask);       /* add the flag     */
    
    return;
}

/*
 * Always sets the flag given.
 */
void
set_reg_flag(uint16_t mask, uint32_t *ctrl_reg)
{
    if(is_reg_mask(mask))
        *ctrl_reg |= mask;

    return;
}

/*
 * Sets the according register flag to 0. 
 */
void
clear_reg_flag(uint16_t mask, uint32_t *ctrl_reg)
{
    if(is_reg_mask(mask))
        *ctrl_reg &= ~mask;

    return;
}
