#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
    Defines all of the macros and prototypes used for analyzing
    instructions for the CPU. This will include masks for defining
    what type of instruction, and more in depth to decipher which
    instruction is being used.
    
    file:       operations.h
    author:     Dave Smith-Hayes
    date:       March 26, 2015
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
#define INST_MASK   0xF000
 
#define DAT_MASK    0xF000      /* data processing      */
#define LS_MASK     0x2000      /* load/store           */
#define IMM_MASK    0x4000      /* immediate            */
#define COND_MASK   0x8000      /* conditional branch   */
#define PP_MASK     0xA000      /* push/pull            */
#define UN_MASK     0xC000      /* unconditional branch */

#define STOP_MASK   0xE000      /* stop                 */

/*
 * Macros that return non-zero if correct mask
 */
#define IS_DAT_INST(x)  ((DAT_MASK & ~x) == DAT_MASK)  ? 1 : 0
#define IS_LS_INST(x)   ((LS_MASK & x) == LS_MASK)     ? 1 : 0
#define IS_IMM_INST(x)  ((IMM_MASK & x) == IMM_MASK)   ? 1 : 0
#define IS_COND_INST(x) ((COND_MASK & x) == COND_MASK) ? 1 : 0
#define IS_PP_INST(x)   ((PP_MASK & x) == PP_MASK)     ? 1 : 0
#define IS_UN_INST(x)   ((UN_MASK & x) == UN_MASK)     ? 1 : 0
#define IS_STOP_INST(x) ((STOP_MASK & x) == STOP_MASK) ? 1 : 0

/*
 * Macros that return non-zero if register flag set
 */
#define IS_SIGN(x)      ((SIGN_MASK & x) == SIGN_MASK) ? 1 : 0
#define IS_ZERO(x)      (x == 0) ? 1 : 0

/*
 * Macros that return the Rn or Rd from specific instruction types
 * that use them, along with the immediate value
 */
#define RN(x)   (x & RN_MASK) >> RN_SHIFT
#define RD(x)   (x & RD_MASK)
#define IMM(x)  (x & IMM_VAL) >> IMM_VAL_SHIFT

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

#define DAT_OPCODE          0x0F00
#define DAT_OPCODE_SHIFT    0xC
#define DAT_GET_OPCODE(x)   (DAT_OPCODE & x) >> DAT_OPCODE_SHIFT

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
#define IMM_VAL_SHIFT    4  /* 4bit shift for this little guy. */

#define IMM_OPCODE  0x7000
#define IMM_GET_OPCODE(x)   (IMM_OPCODE & x)

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

#define COND_OPCODE 0x0F00
#define COND_GET_OPCODE(x)  (COND_OPCODE & x)

#define COND_ADDR   0x00FF
#define COND_GET_ADDR(x)    (COND_ADDR & x)

/*
 * Push/Pull Operations
 */
#define PP_OP_L     0x8000
#define PP_OP_H     0x4000
#define PP_OP_R     0x1000

#define PP_OPCODE   0x0F00
#define PP_GET_OPCODE(x)    (PP_OPCODE & x)

/*
 * Unconditional branches
 */
#define UN_BRA      0xC000
#define UN_BRL      0xD000

#define UN_OFFSET   0x0FFF
#define GET_UN_OFFSET(x)    (UN_OFFSET & x)


/***********************/
/* Function Prototypes */
/***********************/

/*
 * Returns non-zero if the operation produces a carry
 */
uint8_t is_carry(uint32_t op1, uint32_t op2, uint32_t ccr);

/*
 * Get the immediate value in the instruction
 */
uint8_t get_imm(uint16_t inst);


/*
 * flags! flags! flags! (for the registers)
 */
uint8_t is_reg_mask(uint16_t mask);

void toggle_reg_flag(uint16_t mask, uint32_t *ctrl_reg);
void set_reg_flag(uint16_t mask, uint32_t *ctrl_reg);
void clear_reg_flag(uint16_t mask, uint32_t *ctrl_reg);


/*
 * Executes the proper instruction
 */
void execute(uint16_t inst, registers *reg);

/*
 * Performs immediate instructions
 */
void immediate(uint16_t inst, registers *reg);

/*
 * Performs a register to register operations
 */
void data(uint16_t inst, registers *reg);

#endif /* OPERATIONS_H */
