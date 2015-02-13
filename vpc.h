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

#define TOTAL_MEMORY    0x4000  /* 16kB = (16 * 1024B) */
#define INPUT_BUFFER    0xFF    /* 255B */
#define MENU_INPUT_SIZE 0x3     /* 3B input seems to work best. */


/* Inline functions */

inline void 
display_help()
{
    fprintf(stdout, "d\tdump memory\n");
    fprintf(stdout, "g\tgo - run the program\n");
    fprintf(stdout, "l\tload a file into memory\n");
    fprintf(stdout, "m\tmemory modify\n");
    fprintf(stdout, "q\tquit\n");
    fprintf(stdout, "r\tdisplay registers\n");
    fprintf(stdout, "t\ttrace - execute one instruction\n");
    fprintf(stdout, "w\twrite file\n");
    fprintf(stdout, "z\treset all registers to 0\n");
    fprintf(stdout, "?, h\tdisplay this menu\n\n");
}


/* Function prototypes */

void 
write_file(void *memory);

int  
load_file(void *memory, unsigned int max);

void 
dump_memory(char *memory, unsigned int offset, unsigned int length);

void 
modify_memory(void *memory, unsigned int offset);
