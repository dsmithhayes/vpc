/*
    Functions in this file will help retrieve information from the
    16bit instructions that will be used all through out the actual
    operation. This includes getting the Rd or Rn, and confirming that
    the instruction is actually that of the type specified.

    file:       operations.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "operations.h"
#include "registers.h"

/*
 * Pass this a mask like MOV_IMM, and the instruction. Returns true
 * if they match.
 */
uint8_t
is_inst(uint16_t mask, uint16_t inst)
{
    return ((mask & inst) == mask) ? 1 : 0;
}

/*
 * Given the whole 16bit instruction, the Rd of the instruction is
 * always the last 4bits.
 */
uint8_t
get_rd(uint16_t val)
{
    return (val & RD_MASK);
}

/*
 * As with in the Rd, the Rn is 4bits within the 16bit instruction,
 * but rather the 5th to 8th bits.
 */
uint8_t
get_rn(uint16_t val)
{
    return (val & RN_MASK) >> RN_SHIFT;
}
