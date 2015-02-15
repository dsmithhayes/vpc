/*
    file:   modify_memory.c
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
modify_memory(void *memory, unsigned int offset)
{
    char input;
    fprintf(stdout, "modify the memory. enter '.' to end.\n");
    
    while(1) {
        fprintf(stdout, "%4X> ", offset);
        while(getchar() != '\n');
        
        if((input = getchar()) == '.')
            break;
        
        *((char *) memory + offset) = input;
        
        if(++offset == TOTAL_MEMORY)
            break;
    }
    
    return;
}
