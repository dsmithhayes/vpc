/*
    Definitions and variables that represent the registers to the
    virtual processor.

    file:       registers.h
    author:     Dave Smith-Hayes
    date:       March 13th, 2015
*/

/***************/
/* Definitions */
/***************/

/* register file array */
#define REG_FILE_S  0x10    /* Size of reg file */
#define SP          0xD     /* Stack Pointer    */
#define LR          0xE     /* Link Register    */
#define PC          0xF     /* Porgram Counter  */

/* register file */
extern unsigned long registers[REG_FILE_S];

#define SIGN    4   /* 100 */
#define ZERO    2   /* 010 */
#define CARRY   1   /* 001 */
extern unsigned long ccr;   /* Sign, Zero, Carry flags  */

#define REG_SIZE    4       /* 4Byte registers          */
#define REG_BIT_S   0x20    /* 32bit registers          */
#define INSTR_SIZE  2       /* 2Byte instructions       */
#define INS_BIT_S   0x10    /* 16bit instructions       */
extern unsigned long mbr;   /* memory buffer register   */
extern unsigned long mar;   /* memory address register  */
extern unsigned long ir;    /* instruction register     */

unsigned short ir_flag;     /* 0 = IR0, 1 = IR1         */
unsigned short stop_flag;   /* 1 = stop!, 0 = continue  */


/**************/
/* Prototypes */
/**************/

/* Sets all registers to zero */
void zero();

/* Displays all of the registers to the screen. */
void dumpreg();
unsigned int ir0(unsigned long in); /* returns ir0 from ir  */
unsigned int ir1(unsigned long in); /* returns ir1 from ir  */

/* single steps through the program */
void trace();

/* sets the registers accordingly */
void fetch(void *memory);
