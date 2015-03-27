/*
    Functions in this file will help retrieve information from the
    16bit instructions that will be used all through out the actual
    operation. This includes getting the Rd or Rn, and confirming that
    the instruction is actually an instruction

    file:       operations.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

/*******************/
/* System Includes */
/*******************/

#include "operations.h"
#include "registers.h"


/*************/
/* Functions */
/*************/

uint8_t
is_inst(uint16_t mask, uint16_t inst)
{
    return ((mask & inst) == mask) ? 1 : 0;
}

/*
 * Snags the immediate value out of the 2byte representing an
 * immediate operation.
 */
uint8_t
get_imm(uint16_t inst)
{
    return (inst & IMM_VAL) >> IMM_VAL_SHIFT;
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
