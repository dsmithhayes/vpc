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

/* Memory */

#define TOTAL_MEMORY    0x4000  /* 16kB = (16 (0x10) * 1024B (0x400)) */

static char memory[TOTAL_MEMORY];

/* Registers */

#define TOTAL_REG   0x10    /* For the general registers */
#define SP          0xD     /* Stack Pointer */
#define LR          0xE     /* Link Register */
#define PC          0xF     /* Porgram Counter */

static unsigned long registers[TOTAL_REG];   /* general registers */
static unsigned long ccr;                    /* Sign, Zero, Carry flags */
static unsigned long mbr;                    /* memory buffer register */
static unsigned long mar;                    /* memory address register */
static unsigned long ir;                     /* instruction register */

static bool IR_flag = 0;    /* 0 = IR0, 1 = IR1 */
static bool stop_flag = 0;  /* 1 = stop!, 0 = keep going */

/* User Interface */

#define INPUT_BUFFER    0xFF    /* 255B */
#define HEX_INPUT       0x4

/* Function prototypes */

void help();

void
write_file(
    void *memory
);

int 
load_file(
    void *memory,
    unsigned int max
);

void
dump_memory(
    void *memory,
    unsigned int offset,
    unsigned int length
);

void
modify_memory(
    void *memory,
    unsigned int offset
);
