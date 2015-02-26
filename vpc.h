/*
    vpc is a virtual memory program.

    file:       vpc.h
    author:     Dave Smith-Hayes
    date:       February 13th, 2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define TOTAL_MEMORY    0x4000  /* 16kB = (16 (0x10) * 1024B (0x400) */
#define INPUT_BUFFER    0xFF    /* 255B */


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
