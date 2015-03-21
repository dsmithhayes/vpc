#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
    Defines all of the macros and prototypes used for analyzing
    instructions for the CPU.
    
    file:       operations.h
    author:     Dave Smith-Hayes
    date:       March 17, 2015
*/

#include <inttypes.h>
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
 * first nibble:    0000
 * second nibble:   operation
 *      0000 : AND
 *      0001 : EOR
 *      1100 : ORR
 *      0010 : SUB
 *      0100 : ADD
 *      0110 : LSR
 *      0111 : LSL
 *      1110 : MOV
 * third nibble:    Rn
 * fourth nibble:   Rd
 */
#define DAT_AND     0x0000
#define DAT_EOR     0x0100
#define DAT_ORR     0x0C00
#define DAT_SUB     0x0200
#define DAT_ADD     0x0400
#define DAT_LSR     0x0600
#define DAT_LSL     0x0700
#define DAT_MOV     0x0E00

/*
 * Immediate Instructions
 *
 * First nibble:    01[OPCODE]
 *      00 : MOV
 *      01 : CMP
 *      10 : ADD
 *      11 : SUB
 * Next byte:       8bit value
 * Last nibble:     Rd
 */
#define MOV_IMM     0x4000
#define CMP_IMM     0x5000
#define ADD_IMM     0x6000
#define SUB_IMM     0x7000

#define IMM_VAL     0x0FF0

#define IMM_VAL_SHIFT   4       /* 4bit shift for this little guy.  */
#define IMM_INS_SHIFT   0xC     /* 12bit shifts up in here          */

#define IMM_STEP    0x1000

/* Stop */
#define STOP_INST   0xE000


/***********************/
/* Function Prototypes */
/***********************/

/*
 * Returns true if a valid instruction
 */
uint8_t is_inst(uint16_t mask, uint16_t inst);


/*
 * flags! flags! flags!
 */
uint8_t is_mask(uint16_t mask);
void toggle_flg(uint16_t mask, uint32_t *ctrl_reg);
void set_flg(uint16_t mask, uint32_t *ctrl_reg);
void clear_flg(uint16_t mask, uint32_t *ctrl_reg);

/*
 * Executes the proper instruction
 */
void execute(uint16_t inst, registers *reg);

/*
 * Gets the Rd and Rn for the register file index
 */
uint8_t get_rd(uint16_t val);
uint8_t get_rn(uint16_t val);


/*
 * Performs an immediate instruction
 */
void immediate(uint16_t mask, uint16_t inst, registers *reg);

/*
 * Get the immediate value in the instruction
 */
uint8_t get_imm(uint16_t inst);

#endif /* OPERATIONS_H */
