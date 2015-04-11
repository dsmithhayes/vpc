/*
    file:       modmem.c
    author:     Dave Smith-Hayes
    date:       February 13th, 2015
    
    This modifies the memory being held by the program. It asks the 
    user for an offset, and then begins to take in values and changes
    the memory location according. 
    
    everything ends when '.' is detected or the last spot in memory is
    taken.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vpc.h"
#include "interface.h"

void 
modmem(void *memory, uint16_t offset)
{
    char input[HEX_INPUT];
    uint8_t buffer;

    fprintf(stdout, "Modify the memory. enter '.' to end.\n\n");

    /* Failsafe the memory location to manipulate. */
    offset = (offset >= TOTAL_MEMORY) ? 0 : offset;

    /* the program likes having this here? */
    while(getchar() != '\n');
    
    while(1) {
        fprintf(stdout, "%4X> ", offset);

        if(fgets(input, HEX_INPUT, stdin) == NULL) {
            perror("fgets");
            return;
        }
        else
            input[(strlen(input) - 1)] = '\0';

        if(strcmp(input, ".") == 0)
            return;

        fflush(stdout);

        /* stroul() = string to unsigned long */
        buffer = (uint8_t) strtoul(input, NULL, HEX);
        
        /* changed this! */
        *((uint8_t *) memory + offset) = buffer;

        if(++offset == TOTAL_MEMORY)
            return;
    }

    return;
}
