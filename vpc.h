/*
    vpc is a virtual memory program.

    file:       vpc.h
    author:     Dave Smith-Hayes
    date:       February 13th, 2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

/************
 *  Memory  *
 ************/

/* 16kB = (16 (0x10) * 1024B (0x400)) */
#define TOTAL_MEMORY    0x4000
static char memory[TOTAL_MEMORY];

/***************
 *  Registers  *
 ***************/

#define TOTAL_REG   0x10    /* For the general registers */
#define SP          0xD     /* Stack Pointer */
#define LR          0xE     /* Link Register */
#define PC          0xF     /* Porgram Counter */
static unsigned long registers[TOTAL_REG];   /* general registers */

static unsigned long ccr;   /* Sign, Zero, Carry flags */
#define SIGN    4   /* 100 */
#define ZERO    2   /* 010 */
#define CARRY   1   /* 001 */

static unsigned long mbr;   /* memory buffer register */
static unsigned long mar;   /* memory address register */
static unsigned long ir;    /* instruction register */

static bool ir_flag   = 0;  /* 0 = IR0, 1 = IR1 */
static bool stop_flag = 0;  /* 1 = stop!, 0 = keep going */

/********************
 *  User Interface  *
 ********************/

#define INPUT_BUFFER    0xFF    /* 255B input for strings */
#define HEX_INPUT       4       /* 4B for (hex) string values */
#define OUTPUT_MASK     0x000000FF

/*************************
 *  Function prototypes  *
 *************************/

/* Display the usage help. */
void help();

/* Write a file onto the disk. */
void writef(void *memory);

/* Load a file into the memory. */
int  loadf(void *memory, unsigned int max);

/* Dumps the memory to screen. */
void dumpmem(void *memory, unsigned int offset, unsigned int length);

/* Modifies the memory. */
void modmem(void *memory, unsigned int offset);

/* Sets all registers to zero */
void zero();

/* Displays all of the registers to the screen. */
void dumpreg();
unsigned int ir0(unsigned long in);
unsigned int ir1(unsigned long in);

/* Trace the memory and commands. */
void trace();
void fetch();
#define INST_SIZE   4   /* Instruction size in bytes */


/**********
 *  Misc  *
 **********/

#define HEX     0x10
