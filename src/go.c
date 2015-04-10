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
 */
void
go(void *memory, registers *reg)
{
    while(!reg->stop_flag) {
        if(reg->ir_flag) {
            execute(IR1(reg->ir), reg, memory);
            continue;
        }
        else {
            fetch(memory, reg);
            execute(IR0(reg->ir), reg, memory);
        }
    }

    return;
}
