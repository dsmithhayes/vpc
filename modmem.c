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
    unsigned int buffer;
    int i;

    fprintf(stdout, "modify the memory. enter '.' to end.\n");

    /* Failsafe the memory location to manipulate. */
    if(offset >= TOTAL_MEMORY)
        offset = 0;

    while(getchar() != '\n');
    
    while(1) {
        fprintf(stdout, "%4X> ", offset);

        fgets(input, HEX_INPUT, stdin);
        input[(strlen(input) - 1)] = '\0';

        if(strcmp(input, ".") == 0)
            return;
       
        for(i = 0; i < strlen(input); i++)
            if(!isxdigit((int) input[i]))
                break;

        sscanf(input, "%2X", &buffer);
 
        *((char *) memory + offset) = (char) buffer;

        if(++offset == TOTAL_MEMORY)
            return;
    }

    return;    
}
