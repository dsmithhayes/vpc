/*
    vpc is a virtual memory program.

    author:     Dave Smith-Hayes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_MEMORY    16000U  /*  16 kB; 0xe80 */
#define INPUT_BUFFER    256u    /* 256  B; 0x100 */ 
#define MENU_INPUT_SIZE 3u      /*   3  B; 0x3 */


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
dump_memory(void *memory, unsigned int offset, unsigned int length);

void 
modify_memory(void *memory, unsigned int offset);
