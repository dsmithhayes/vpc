/*
    file:   modmem.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    This modifies the memory being held by the program. It asks the 
    user for an offset, and then begins to take in values and changes
    the memory location according. 
    
    everything ends when '.' is detected or the last spot in memory is
    taken.
*/

#include "vpc.h"


void 
modmem(void *memory, unsigned int offset)
{
    char input[HEX_INPUT];
    unsigned long buffer;

    fprintf(stdout, "modify the memory. enter '.' to end.\n");

    /* Failsafe the memory location to manipulate. */
    if(offset >= TOTAL_MEMORY)
        offset = 0;

    /* the program likes having this here? */
    while(getchar() != '\n');
    
    while(1) {
        fprintf(stdout, "%4X> ", offset);

        if(fgets(input, HEX_INPUT, stdin) == NULL) {
            perror("fgets");
            return;
        }
        else
            input[(strlen(input) - 1)] = '\0';  /* kill the \n */

        if(strcmp(input, ".") == 0)
            return;

        if((buffer = strtoul(input, NULL, HEX)) == ULONG_MAX) {
            perror("strtoul");
            return;
        }
        
        /* change this? */
        *((char *) memory + offset) = buffer;

        if(++offset == TOTAL_MEMORY)
            return;
    }

    return;
}
