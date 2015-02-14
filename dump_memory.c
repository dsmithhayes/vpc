/*
    file:   dump_memory.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    dump_memory() is arbitrarily called with values. Who knows how it
    will act if you supply an offset larger than the memory, but who
    knows! The user interface will prevent this from happening.
    
    The value of each memory location is printed on the screen unless
    its not human readable and then it is represented with a '.'
*/

#include "vpc.h"

void
dump_memory(void *memory, unsigned int offset, unsigned int length)
{
    unsigned int i, j;
    unsigned int row_start;
    
    /* holds the row numbers. */
    unsigned int row_s = 0x10;
    unsigned int total_rows = (TOTAL_MEMORY / row_s);
    unsigned int row_offset[total_rows];
    
    /* builds the row numbers, determines where to start */
    for(i = 0; i < total_rows; i++) {
        row_offset[i] = (row_offset[(i - 1)] * row_s);
        
        if((offset < row_offset[i])
                && offset >= (row_offset[(i - 1)]))
            row_start = (i - 1);
    }
    
    /* prints the lines */
    for(i = row_start; i < total_rows; i++) {
        fprintf(stdout, "%o\t", row_offset[i]);
        
        /* first row, get the start */
        if(i == row_start)
            offset = (offset - row_offset[row_start]);
        
        for(j = offset; j < TOTAL_MEMORY; j++)
            fprintf(stdout, "%o ", (unsigned short) *(memory + j));
        
        fprintf(stdout, "\n\t");
        
        for(j = offset; j < TOTAL_MEMORY; j++)
            if(isprint((int) *(memory + j)))
                fprintf(stdout, "%c ", (char) *(memory + j));
            else
                fprintf(stdout, ". ");
        
        fprintf(stdout, "\n");
        offset += row_s;
    }
}
