/*
    file:   dump_memory.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    Arbitraily displays the contents of memory.
    
    The value of each memory location is printed on the screen unless
    its not human readable and then it is represented with a '.'
*/

#include "vpc.h"

void
dumpmem(void *memory, unsigned int offset, unsigned int length)
{
    unsigned int i, j;
    unsigned int row_length = 0x10;
    
    length--;   /* for some reason it needs this? */
    
    for(i = offset; i < (offset + length); i += row_length) {
        /* the row off set number */
        fprintf(stdout, "%4X\t", i);
        
        /* top row of the display, just the hex value in memory */
        for(j = i; j < (i + row_length); j++) {
            fprintf(stdout, "%2X ", *((char *) memory + j)
                    & OUTPUT_MASK);

            if(j == (offset + length))
                break;
        }
        
        fprintf(stdout, "\n\t");
        
        /* the contents of the memory */
        for(j = i; j < (i + row_length); j++) {
            if(isprint((int) *((char *) memory + j)))
                fprintf(stdout, " %c ", *((char *) memory + j));
            else
                fprintf(stdout, " . ");
            
            if(j == (offset + length))
                break;
        }
        
        fprintf(stdout, "\n");
        
        /* stop the routine if its reached the limit. */
        if(j == length)
            break;
    }
    
    return;
}
