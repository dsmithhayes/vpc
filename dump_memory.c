#include "vpc.h"

/*
    Prints a memory dump to the screen from the offset using the
    memory location.
*/
void
dump(char *memory, unsigned int offset, unsigned int length)
{
    unsigned int i, j;
    unsigned int row_start;
    
    /* holds the row numbers. */
    unsigned short row_s = 16;
    unsigned int row_offset[(TOTAL_MEMORY / row_s)];
    
    /* error checking */
    if(offset > (TOTAL_MEMORY - 1)) {
        printf("Not in the memory range.\n");
        return;
    }
    
    /* builds the row numbers, determines where to start */
    for(i = 0; i < (TOTAL_MEMORY / row_s); i++) {
        row_offset[i] = (row_offset[(i - 1)] * row_s);
        
        if((row_offset[i] > offset) 
                && (row_offset[(i - 1)] <= offset))
            row_start = (i - 1);
    }
    
    for(i = row_start; i < (TOTAL_MEMORY / row_s); i++) {
        fprintf(stdout, "%o\t", row_offset[i]);
        
        /* first row, get the start */
        if(i == row_start)
            offset = (offset - row_offset[row_start]);
        
        for(j = offset; j < TOTAL_MEMORY; j++)
            fprintf(stdout, "%o ", (unsigned short) *(memory + j));
        
        fprintf(stdout, "\n\t");
        
        for(j = offset; j < TOTAL_MEMORY; j++)
            fprintf(stdout, "%c ", (char) *(memory + j));
        
        offset += row_s;
    }
}
