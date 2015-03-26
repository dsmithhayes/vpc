/*
    file:   dump_memory.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    Arbitraily displays the contents of memory.
    
    The value of each memory location is printed on the screen unless
    its not human readable and then it is represented with a '.'
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "vpc.h"
#include "interface.h"


void
dumpmem(void *memory, uint16_t offset, uint16_t length)
{
    uint16_t i, j;
    
    length--;   /* for some reason it needs this? */
    
    for(i = offset; i < (offset + length); i += ROW_LENGTH) {
        /* the row off set number */
        fprintf(stdout, "%4X\t", i);
        
        /* top row of the display, just the hex value in memory */
        for(j = i; j < (i + ROW_LENGTH); j++) {
            fprintf(stdout, "%2X ", *((uint8_t *) memory + j));

            if(j == (offset + length))
                break;
        }
        
        fprintf(stdout, "\n\t");
        
        /* the contents of the memory */
        for(j = i; j < (i + ROW_LENGTH); j++) {
            if(isprint((int) *((uint8_t *) memory + j)))
                fprintf(stdout, " %c ", *((uint8_t *) memory + j));
            else
                fprintf(stdout, " . ");
            
            if(j == (offset + length))
                break;
        }
        
        fprintf(stdout, "\n");
        
        /* stop the routine if its reached the limit. */
        if(j == length)
            return;
    }

    return;
}
