#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
    Defines all of the macros and prototypes used for analyzing
    instructions for the CPU.
    
    file:       operations.h
    author:     Dave Smith-Hayes
    date:       March 17, 2015
*/

#include "registers.h"

/*********************/
/* Instruction Masks */
/*********************/

#define RD_MASK     0x000F
#define RN_MASK     0x00F0

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
#define DAT_AND     0x00FF
#define DAT_EOR     0x01FF
#define DAT_ORR     0x0CFF
#define DAT_SUB     0x02FF
#define DAT_ADD     0x04FF
#define DAT_LSR     0x06FF
#define DAT_LSL     0x07FF
#define DAT_MOV     0x0EFF

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
#define MOV_IMM     0x4FFF
#define CMP_IMM     0x5FFF
#define ADD_IMM     0x6FFF
#define SUB_IMM     0x7FFF

#define IMM_VAL     0x0FF0
#define IMM_SHIFT   0x10

#define IMM_STEP    0x1000

/* Stop */
#define STOP_INST   0xE000


/***********************/
/* Function Prototypes */
/***********************/

/* Returns true if a valid instruction */
unsigned short is_inst(unsigned int mask, unsigned int inst);


/* flags! flags! flags! */
void toggle_flg(unsigned int mask, unsigned long *ctrl_reg);
void set_flg(unsigned int mask, unsigned long *ctrl_reg);
void clear_flg(unsigned int mask, unsigned long *ctrl_reg);

/* Executes the proper instruction */
void execute(unsigned int inst, registers *reg);

/* Gets the Rd and Rn for the register file index */
unsigned int get_rd(unsigned int val);
unsigned int get_rn(unsigned int val);


/* Performs an immediate instruction */
void immediate(
        unsigned int mask,
        unsigned int inst,
        registers *reg);

/* Get the immediate value in the instruction, right bitshift of 4 */
unsigned int get_imm(unsigned int inst);

#endif /* OPERATIONS_H */
