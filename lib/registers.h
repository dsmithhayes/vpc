#ifndef REGISTERS_H
#define REGISTERS_H

/*
    Definitions and variables that represent the registers to the
    virtual processor.

    file:       registers.h
    author:     Dave Smith-Hayes
    date:       March 13th, 2015
*/

/*******************/
/* System Includes */
/*******************/
#include <stdint.h>


/***************/
/* Definitions */
/***************/

/* Special Registers & Register File */
#define REG_FILE_S  0x10    /* Size of reg file */
#define SP          0xD     /* Stack Pointer    */
#define LR          0xE     /* Link Register    */
#define PC          0xF     /* Porgram Counter  */


/* Flags */
#define SIGN    4   /* 100 */
#define ZERO    2   /* 010 */
#define CARRY   1   /* 001 */

#define STOP    1
#define INST    1

#define SIGN_MASK   0x80000000

/* Registers & Instructions */
#define REG_SIZE    4       /* 4Byte registers      */
#define REG_BIT_S   0x20    /* 32bit registers      */
#define INSTR_SIZE  2       /* 2Byte instructions   */
#define INS_BIT_S   0x10    /* 16bit instructions   */


/*
 * The registers struct is just an easy way to move and use the
 * registers with how the program is designed.
 *
 * file[]   register file, macros SP, LR and PC are used here.
 *
 * ccr      code control registers, has the sign, zero and carry
 *          flags, where SZC (000) = Sign, Zero Carry. Macros SIGN,
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
 *          and ir0 and ir1 pseudo register. Functions ir0() and ir1()
 *          are used to split the register.
 *
 * ir_flg   determines which instruction register is being used
 *
 * stp_flg  tells the program to stop its execution.
 * 
 */

typedef struct Registers {
    uint32_t file[REG_FILE_S];
    
    uint32_t ccr;
    uint32_t mbr;
    uint32_t mar;
    uint32_t ir;
    uint32_t alu;
    
    uint8_t ir_flg;
    uint8_t stp_flg;
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
uint16_t ir0(uint32_t in); /* returns ir0 from ir  */
uint16_t ir1(uint32_t in); /* returns ir1 from ir  */

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
