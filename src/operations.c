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


/*******************/
/* Arrays of Masks */
/*******************/

/*
 * Instruction masks
 */
uint16_t inst_mask[TOTAL_INST] = {
    DAT_MASK, LS_MASK, IMM_MASK,
    COND_MASK, PP_MASK, UN_MASK,
    STOP_MASK
};

/*
 * Immediate instructions
 */
uint16_t imm_inst_mask[TOTAL_IMM] = {
    MOV_IMM, CMP_IMM,
    ADD_IMM, SUB_IMM
};

/*
 * Data instructions
 */
uint16_t data_inst_mask[TOTAL_DATA] = {
    AND_DAT, EOR_DAT, SUB_DAT, SXB_DAT,
    ADD_DAT, ADC_DAT, LSR_DAT, LSL_DAT,
    TST_DAT, TEQ_DAT, CMP_DAT, ROR_DAT,
    ORR_DAT, MOV_DAT, BIC_DAT, MVN_DAT
};

/*
 * Conditional instructions
 */
uint16_t cond_inst_mask[TOTAL_COND] = {
    COND_CC, COND_CS, COND_EQ, COND_HI,
    COND_LS, COND_MASK, COND_MI, COND_NE,
    COND_PL, COND_STEP
}


/*************/
/* Functions */
/*************/

/*
 * Pass this a mask like MOV_IMM, and the instruction. Returns true
 * if they match.
 */
uint8_t
is_inst(uint16_t inst)
{
    int i;

    for(i = 0; i < TOTAL_INST; i++)
        if((inst_mask[i] & inst) == inst_mask[i])
            return inst_mask[i];

    return 0;
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
