#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
    Defines all of the macros and prototypes used for analyzing
    instructions for the CPU.
    
    file:       operations.h
    author:     Dave Smith-Hayes
    date:       March 17, 2015
*/


/*******************/
/* System Includes */
/*******************/

#include <stdint.h>
#include "registers.h"


/*********************/
/* Instruction Masks */
/*********************/

#define RD_MASK     0x000F
#define RN_MASK     0x00F0

#define RN_SHIFT    4

/*
 * Data Processing Instructions
 *
 * 0000ppppNNNNDDDD
 * 
 * first nibble:    0000
 * second nibble:   pppp = opcode
 *      0000 : AND
 *      0001 : EOR
 *      1100 : ORR
 *      0010 : SUB
 *      0100 : ADD
 *      0110 : LSR
 *      0111 : LSL
 *      1110 : MOV
 * third nibble:    NNNN = Rn, register source
 * fourth nibble:   DDDD = Rd, register destination
 */
#define AND_DAT     0x0000
#define EOR_DAT     0x0100
#define ORR_DAT     0x0C00
#define SUB_DAT     0x0200
#define ADD_DAT     0x0400
#define LSR_DAT     0x0600
#define LSL_DAT     0x0700
#define MOV_DAT     0x0E00


/*
 * Immediate Instructions
 *
 * 01ppiiiiiiiiDDDD
 *
 * First nibble:    01pp; where nn = opcode
 *      00 : MOV
 *      01 : CMP
 *      10 : ADD
 *      11 : SUB
 * Next byte:       iiiiiiii = 8bit immediate value
 * Last nibble:     DDDD = Rd, register destination
 */
#define MOV_IMM     0x4000
#define CMP_IMM     0x5000
#define ADD_IMM     0x6000
#define SUB_IMM     0x7000

#define IMM_VAL     0x0FF0

#define IMM_VAL_SHIFT   4       /* 4bit shift for this little guy. */

#define IMM_STEP    0x1000

/*
 * The stop instruction
 */
#define STOP_INST   0xE000


/*
 * This is a handy array of all the instruction masks that
 * may be used to test if an instruction is valid.
 */
uint16_t inst_masks[] = {
    /*
     * Data instructions (reg to reg)
     */
    ADD_DAT,
    EOR_DAT,
    ORR_DAT,
    SUB_DAT,
    ADD_DAT,
    LSR_DAT,
    LSL_DAT,
    MOV_DAT,

    /*
     * Immediate instructions
     */
    MOV_IMM,
    CMP_IMM,
    ADD_IMM,
    SUB_IMM,

    /*
     * Stop instruction
     */
    STOP_INST
}

/*
 * Dynamically allocate how many instructions are listed
 */
#define TOTAL_INST  sizeof(inst_masks) / sizeof(uint16_t)


/***********************/
/* Function Prototypes */
/***********************/

/*
 * Returns true if a valid instruction
 */
uint8_t is_inst(uint16_t mask, uint16_t inst);

/*
 * Get the immediate value in the instruction
 */
uint8_t get_imm(uint16_t inst);

/*
 * Gets the Rd and Rn for the register file index
 */
uint8_t get_rd(uint16_t val);
uint8_t get_rn(uint16_t val);


/*
 * Is it even a mask?
 */
uint8_t is_mask(uint16_t mask);

/*
 * flags! flags! flags!
 */
void toggle_flg(uint16_t mask, uint32_t *ctrl_reg);
void set_flg(uint16_t mask, uint32_t *ctrl_reg);
void clear_flg(uint16_t mask, uint32_t *ctrl_reg);


/*
 * Executes the proper instruction
 */
void execute(uint16_t inst, registers *reg);

/*
 * Performs an immediate instruction
 */
void immediate(uint16_t mask, uint16_t inst, registers *reg);

/*
 * Performs a register to register operation.
 */
void data(uint16_t mask, uint16_t inst, registers *reg);


#endif /* OPERATIONS_H */
