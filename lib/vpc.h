/*
    vpc is a virtual processor. It had 32bit registers and uses 16bit
    instructions.

    file:       vpc.h
    author:     Dave Smith-Hayes
    date:       February 13th, 2015
*/

/* 16kB = (16 (0x10) * 1024B (0x400)) */
#define TOTAL_MEMORY    0x4000


/*************************/
/*  Function prototypes  */
/*************************/

/* Write a file onto the disk. */
void writef(void *memory);

/* Load a file into the memory. */
int loadf(void *memory, unsigned int max);

/* Dumps the memory to screen. */
void dumpmem(void *memory, unsigned int offset, unsigned int length);

/* Modifies the memory. */
void modmem(void *memory, unsigned int offset);

/* Makes the program run */
void go(void *memory, struct registers *reg);


/**********/
/*  Misc  */
/**********/

#define HEX 0x10
