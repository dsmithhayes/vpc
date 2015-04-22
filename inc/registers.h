#ifndef REGISTERS_H
#define REGISTERS_H

/*
    Definitions and variables that represent the registers to the
    virtual processor.

    file:       registers.h
    author:     Dave Smith-Hayes
    date:       April 8, 2015
*/

/*******************/
/* System Includes */
/*******************/

#include <stdint.h>


/***************/
/* Definitions */
/***************/

/*
 * Special Registers & Register File
 */
#define REG_FILE_S  0x10    /* Size of reg file */
#define SP          0xD     /* Stack Pointer    */
#define LR          0xE     /* Link Register    */
#define PC          0xF     /* Porgram Counter  */

/*
 * Flags
 */
#define SIGN_FLAG   4   /* 100 */
#define ZERO_FLAG   2   /* 010 */
#define CARRY_FLAG  1   /* 001 */

#define STOP_FLAG   1
#define INST_FLAG   1

#define IS_SIGN_SET(x)  (SIGN_FLAG & x) ? 1 : 0
#define IS_ZERO_SET(x)  (ZERO_FLAG & x) ? 1 : 0
#define IS_CARRY_SET(x) (CARRY_FLAG & x) ? 1 : 0

#define IS_STOP_SET(x)  (STOP_FLAG & x) ? 1 : 0
#define WHICH_IR(x)     (INST_FLAG & x) ? 1 : 0

/*
 * Byte stuff is here
 */
#define BYTE        8
#define BYTE_MASK   0xFF

#define SIGN_MASK   0x80000000
#define MSB_MASK    0x80000000
#define LSB_MASK    1

#define HAS_MSB(x)  ((MSB_MASK & x) == MSB_MASK) ? 1 : 0
#define HAS_LSB(x)  ((LSB_MASK & x) == LSB_MASK) ? 1 : 0

/*
 * This is used in the loadstore() function to break down
 * the 32bit register into single byte chunks.
 */
#define BYTE_1(x)   (0xFF & x)
#define BYTE_2(x)   ((0xFF00 & x) >> BYTE)
#define BYTE_3(x)   ((0xFF0000 & x) >> (BYTE * 2))
#define BYTE_4(x)   ((0xFF000000 & x) >> (BYTE * 3))

/*
 * Registers & Instructions
 */
#define REG_SIZE    4       /* 4Byte registers      */
#define REG_BIT_S   0x20    /* 32bit registers      */
#define INSTR_SIZE  2       /* 2Byte instructions   */
#define INS_BIT_S   0x10    /* 16bit instructions   */

/*
 * Returns the appropriate Instruction Register
 */
#define IR0_MASK    0xFFFF0000
#define IR1_MASK    0x0000FFFF
#define IR0(x)      (x & IR0_MASK) >> INS_BIT_S
#define IR1(x)      (x & IR1_MASK)

/*
 * The registers struct is just an easy way to move and use the
 * registers with how the program is designed.
 *
 * file[]   register file, constants SP, LR and PC are used here as the
 *          index for the array. Example: file[SP] is the Stack Pointer.
 *
 * ccr      code control registers, has the sign, zero and carry
 *          flags, where SZC (000) = Sign, Zero Carry. Constants SIGN,
 *          ZERO and CARRY represent the bits, use bitwise operators
 *          here to test for flags.
 *
 * mbr      Memory Buffer Register holds the data that was fetched
 *          from memory pointed to by the Memory Address Register.
 *
 * mar      Memory Address Register contains the location of the
 *          next register size (4Bytes) of data is located.
 *
 * ir       Instruction Register is a 32bit register that holds the
 *          first and second instruction from memory. This creates
 *          and ir0 and ir1 pseudo register. Macros IR0() and IR1()
 *          are used to split the register.
 *
 * alu      the Arithmetic Logical Unit is actually the register that
 *          performs all of the necessary mathematical expressions for
 *          the instruction.
 *
 * ir_flag      determines which instruction register is being used
 *
 * stop_flag    tells the program to stop its execution.
 * 
 */

typedef struct Registers {
    uint32_t file[REG_FILE_S];
    
    uint32_t ccr;
    uint32_t mbr;
    uint32_t mar;
    uint32_t ir;
    uint32_t alu;

    uint8_t ir_flag;
    uint8_t stop_flag;
} registers;


/**************/
/* Prototypes */
/**************/

/*
 * Sets all registers to zero
 */
void zero(registers *reg);

/*
 * Displays all of the registers to the screen.
 */
void dumpreg(registers reg);

/*
 * single steps through the program
 */
void trace(void *memory, registers *reg);

/*
 * sets the registers accordingly
 */
void fetch(void *memory, registers *reg);

/*
 * Makes the program run
 */
void go(void *memory, registers *reg);

#endif /* REGISTERS_H */
