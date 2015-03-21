/*
    This file houses an awesome function which will fetch forever
    until the stop flag is set.

    file:       go.c
    author:     Dave Smith-Hayes
    date:       March 16th, 2015
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"

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
    while(!reg->stp_flg) {
        if(reg->ir_flg) {
            execute(ir1(reg->ir), reg);
            continue;
        }
        else {
            fetch(memory, reg);
            execute(ir0(reg->ir), reg);
        }
    }

    return;
}
