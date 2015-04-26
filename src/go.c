/*
    file:       go.c
    author:     Dave Smith-Hayes
    date:       March 16th, 2015
    
    This file houses an awesome function which will fetch forever
    until the stop flag is set.
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"
#include "operations.h"

/*
 * If the instruction flag isn't set, fetch new instructions, execute
 * the first instruction and reloop with a set instruction flag. If
 * the instruction flag is set, execute the instruction and reloop.
 *
 * note: each execute() call toggles the instruction flag.
 *
 * after the execution there will be N periods after "Running" showing
 * all of the instructions save for the stop.
 */
void
go(void *memory, registers *reg)
{
    if(reg->stop_flag)  /* can't make a stopped program run... */
        return;
    
    fprintf(stdout, "Running");
    
    while(reg->stop_flag == 0) {
        if(reg->ir_flag) {
            execute((uint16_t) IR1(reg->ir), reg, memory);
            continue;
        }
        else {
            fetch(memory, reg);
            execute((uint16_t) IR0(reg->ir), reg, memory);
        }

        fprintf(stdout, ".");
    }

    fprintf(stdout, "\nFinished.\n");

    return;
}
