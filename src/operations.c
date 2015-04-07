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

/*
 * I don't like this logic, there is a better way.
 */
uint8_t
is_inst(uint16_t inst)
{
    if(IS_IMM_INST(inst))
        return 1;

    if(IS_DAT_INST(inst))
        return 1;

    if(IS_LS_INST(inst))
        return 1;
    
    if(IS_COND_INST(inst))
        return 1;

    if(IS_UN_INST(inst))
        return 1;

    if(IS_STOP_INST(inst))
        return 1;

    return 0;
}

/*
 * Returns non-zero value if the operation is going to cause a carry.
 */
uint8_t
is_carry(uint32_t op1, uint32_t op2, uint32_t ccr)
{
    if((op2 == UINT32_MAX) && (IS_CARRY_SET(ccr)))
        return 1;
    
    return (op1 > (UINT32_MAX - op2 - IS_CARRY_SET(ccr))) ? 1 : 0;
}

/*
 * Sets all the register flags for everything accordingly.
 *
 * sign
 * zero
 * carry
 */
void
scz(uint32_t  alu,
    uint8_t   rd,
    uint8_t   rn,
    uint32_t *ccr)
{
    if(IS_SIGN(alu))
        set_reg_flag(SIGN_FLAG, ccr);
    else
        clear_reg_flag(SIGN_FLAG, ccr);

    if(is_carry(rd, rn, IS_CARRY_SET(*ccr)))
        set_reg_flag(CARRY_FLAG, ccr);
    else
        clear_reg_flag(CARRY_FLAG, ccr);

    if(IS_ZERO(alu))
        clear_reg_flag(ZERO_FLAG, ccr);
    else
        clear_reg_flag(ZERO_FLAG, ccr);

    return;
}

/*
 * This is the same as above, but without the check of the carry.
 */
void
sz(uint32_t alu, uint32_t *ccr)
{
    if(IS_SIGN(alu))
        set_reg_flag(SIGN_FLAG, ccr);
    else
        clear_reg_flag(SIGN_FLAG, ccr);

    if(IS_ZERO(alu))
        clear_reg_flag(ZERO_FLAG, ccr);
    else
        clear_reg_flag(ZERO_FLAG, ccr);
}
