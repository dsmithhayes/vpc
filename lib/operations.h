#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
    Defines all of the macros and prototypes used for analyzing
    instructions for the CPU. This will include masks for defining
    what type of instruction, and more in depth to decipher which
    instruction is being used.
    
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
 * Check first byte for instruction type
 */
#define DAT_MASK    0
#define LS_MASK     0x2000
#define IMM_MASK    0x7000
#define COND_MASK   0x8000
#define PP_MASK     0xA000
#define UBRA_MASK   0xC000
#define UBRL_MASK   0xD000
#define STOP_MASK   0xE000


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
#define SUB_DAT     0x0200
#define SXB_DAT     0x0300
#define ADD_DAT     0x0400
#define ADC_DAT     0x0500
#define LSR_DAT     0x0600
#define LSL_DAT     0x0700
#define TST_DAT     0x0800
#define TEQ_DAT     0x0900
#define CMP_DAT     0x0A00
#define ROR_DAT     0x0B00
#define ORR_DAT     0x0C00
#define MOV_DAT     0x0D00
#define BIC_DAT     0x0E00
#define MVN_DAT     0x0F00

#define DAT_STEP    0x0100

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
 * Conditional Code Masks used for conditional branches
 */
#define COND_EQ     0x8000
#define COND_NE     0x8100
#define COND_CS     0x8200
#define COND_CC     0x8300
#define COND_MI     0x8400
#define COND_PL     0x8500
#define COND_HI     0x8800
#define COND_LS     0x8900

#defien COND_STEP   0x0100

/*
 * Unconditional branches
 */
#define UN_BRA      0xC000
#define UN_BRL      0xD000


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
