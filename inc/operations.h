#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
    file:       operations.h
    author:     Dave Smith-Hayes
    date:       March 26, 2015
    
    Defines all of the macros and prototypes used for analyzing
    instructions for the CPU. This will include masks for defining
    what type of instruction, and more in depth to decipher which
    instruction is being used.
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
#define INST_MASK   0xE000
 
#define DAT_MASK    0xF000      /* data processing      */
#define LS_MASK     0x2000      /* load/store           */
#define IMM_MASK    0x4000      /* immediate            */
#define IMM_MASK_2  0x6000      /* why? */
#define COND_MASK   0x8000      /* conditional branch   */
#define PP_MASK     0xA000      /* push/pull            */
#define UN_MASK     0xC000      /* unconditional branch */

#define STOP_MASK   0xE000      /* stop                 */

/*
 * Macros that return non-zero if correct mask
 */
#define IS_DAT_INST(x)  ((INST_MASK & ~x) == DAT_MASK) ? 1 : 0
#define IS_LS_INST(x)   ((INST_MASK & x) == LS_MASK)   ? 1 : 0
#define IS_IMM_INST(x)  (((INST_MASK & x) == IMM_MASK) \
                        || ((INST_MASK & x) == IMM_MASK_2))  ? 1 : 0
#define IS_COND_INST(x) ((INST_MASK & x) == COND_MASK) ? 1 : 0
#define IS_PP_INST(x)   ((INST_MASK & x) == PP_MASK)   ? 1 : 0
#define IS_UN_INST(x)   ((INST_MASK & x) == UN_MASK)   ? 1 : 0
#define IS_STOP_INST(x) ((INST_MASK & x) == STOP_MASK) ? 1 : 0

/*
 * Macros that return non-zero if register flag set
 */
#define IS_SIGN(x) ((SIGN_MASK & x) == SIGN_MASK) ? 1 : 0
#define IS_ZERO(x) (x == 0) ? 1 : 0

/*
 * Macros that return the Rn or Rd from specific instruction types
 * that use them.
 */
#define RN(x)   ((x & RN_MASK) >> RN_SHIFT)
#define RD(x)   (x & RD_MASK)

/*
 * Data Processing Instructions.
 *
 * 0000ppppNNNNDDDD
 * 
 * first nibble:    0000
 * second nibble:   pppp = opcode
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
#define DAT_OPCODE_SHIFT    8
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

/*
 * Macro to return the immdiate value of the operation
 */
#define IMM(x)  ((x & IMM_VAL) >> IMM_VAL_SHIFT)

#define IMM_OPCODE          0x7000
#define IMM_GET_OPCODE(x)   (IMM_OPCODE & x)

/*
 * Load/Store instructions are basic. Load data from memory into a
 * register or store the data in a register into memory. The L and B
 * represent the Load/Store operation and the Byte/Word operations.
 *
 * This operation uses Rn and Rd respectively.
 * 
 * IS_LS_LOAD(x) will be 0 if its a Store, Load if 1
 * IS_LS_DWORD(x) will be 0 if its a Byte, Double Word if 1
 *
 * 0010LB00NNNNDDDD
 *
 * First nibble:    0010; the instruction identifier
 * Second nibble:
 *      L : value is 1 if load operation, 0 if stroe operation
 *      B : value is 1 if word, 0 if byte
 *      0 : not used
 *      0 : not used
 * Third nibble:    Rn
 * Fourth nibble:   Rd
 */
#define LS_L_MASK   0x0800  /* 1000 */
#define LS_B_MASK   0x0400  /* 0100 */

#define IS_LS_LOAD(x)   ((LS_L_MASK & x) == LS_L_MASK) ? 1 : 0
#define IS_LS_DWORD(x)  ((LS_B_MASK & x) == LS_B_MASK) ? 1 : 0

/*
 * Conditional Code Masks used for conditional branches
 */
#define COND_EQ     0x8000  /* equal                    */
#define COND_NE     0x8100  /* not equal                */
#define COND_CS     0x8200  /* unsigned, higher or same */
#define COND_CC     0x8300  /* unsigned, lower          */
#define COND_MI     0x8400  /* negative                 */
#define COND_PL     0x8500  /* positive                 */
#define COND_HI     0x8800  /* unsigned higher          */
#define COND_LS     0x8900  /* unsigned lower or same   */
#define COND_AL     0x8E00  /* all ignored              */

#define COND_OPCODE 0x0F00
#define COND_GET_OPCODE(x)  (COND_OPCODE & x)

#define COND_ADDR   0x00FF
#define COND_GET_ADDR(x)    (COND_ADDR & x)

/*
 * Push/Pull Operations
 */
#define PP_OP_L     0x0800  /* load/store bit, 1 = load     */
#define PP_OP_H     0x0400  /* high/low registers, 1 = high */
#define PP_OP_R     0x0100  /* pull PC, push LR             */

#define PP_OPCODE   0x0F00

#define PP_REG      0x00FF  /* MSB = highest reg, LSB = lowest */

/*
 * These will define which set of registers will be used
 */
#define PP_REG_1    0x01    /* 00000001 */
#define PP_REG_2    0x02    /* 00000010 */
#define PP_REG_3    0x04    /* 00000100 */
#define PP_REG_4    0x08    /* 00001000 */
#define PP_REG_5    0x10    /* 00010000 */
#define PP_REG_6    0x20    /* 00100000 */
#define PP_REG_7    0x40    /* 01000000 */
#define PP_REG_8    0x80    /* 10000000 */

#define PP_GET_OPCODE(x)    (PP_OPCODE & x)
#define PP_GET_REG(x)       (PP_REG & x)

#define PP_PUSH(x)  (PP_GET_OPCODE(x) == PP_OP_L) ? 1 : 0
#define PP_HIGH(x)  (PP_GET_OPCODE(x) == PP_OP_H) ? 1 : 0
#define PP_EXTRA(x) (PP_GET_OPCODE(x) == PP_OP_R) ? 1 : 0



/*
 * Unconditional branches, there is a branch with link register and
 * branch without. Rather simple operations.
 */
#define UN_BRA      0xC000
#define UN_BRL      0xD000

#define IS_UN_BRA(x)    ((UN_BRA & x) == UN_BRA) ? 1 : 0
#define IS_UN_BRL(x)    ((UN_BRL & x) == UN_BRL) ? 1 : 0

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
 * Set the sign, carry or zero flags.
 */
void scz(registers *reg, uint32_t op1, uint32_t op2);
void sz(registers *reg);


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
void execute(uint16_t inst, registers *reg, void *memory);

/*
 * Performs an immediate instruction
 */
void immediate(uint16_t inst, registers *reg);

/*
 * Performs a register to register operation
 */
void data(uint16_t inst, registers *reg);

/*
 * Load/Store operations
 */
void loadstore(uint16_t inst, registers *reg, void *memory);

/*
 * Conditional Branches
 */
void cond(uint16_t inst, registers *reg);

/*
 * Unconditional Branches
 */
void uncond(uint16_t inst, registers *reg, void *memory);

/*
 * Push/Pull Instructions
 */
void pushpull(uint16_t inst, registers *reg, void *memory);
void push(uint32_t reg, uint32_t *mar, void *memory);
void pull(uint32_t *reg, uint32_t *mar, void *memory);

#endif /* OPERATIONS_H */
