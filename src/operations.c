/*
    file:       operations.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
    
    Functions in this file will help retrieve information from the
    16bit instructions that will be used all through out the actual
    operation. This includes getting the Rd or Rn, and confirming that
    the instruction is actually an instruction
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
scz(registers *reg, uint32_t op1, uint32_t op2)
{
    /*
     * SIGN
     */
    if(IS_SIGN(reg->alu))
        set_reg_flag(SIGN_FLAG, &(reg->ccr));
    else
        clear_reg_flag(SIGN_FLAG, &(reg->ccr));

    /*
     * CARRY
     */
    if(is_carry(op1, op2, IS_CARRY_SET(reg->ccr)))
        set_reg_flag(CARRY_FLAG, &(reg->ccr));
    else
        clear_reg_flag(CARRY_FLAG, &(reg->ccr));

    /*
     * ZERO
     */
    if(IS_ZERO(reg->alu))
        set_reg_flag(ZERO_FLAG, &(reg->ccr));
    else
        clear_reg_flag(ZERO_FLAG, &(reg->ccr));

    return;
}

/*
 * This is the same as above, but without the check of the carry.
 */
void
sz(registers *reg)
{
    if(IS_SIGN(reg->alu))
        set_reg_flag(SIGN_FLAG, &(reg->ccr));
    else
        clear_reg_flag(SIGN_FLAG, &(reg->ccr));

    if(IS_ZERO(reg->alu))
        set_reg_flag(ZERO_FLAG, &(reg->ccr));
    else
        clear_reg_flag(ZERO_FLAG, &(reg->ccr));
}
