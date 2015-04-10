/*
    file:       pushpull.c
    author:     Dave Smith-Hayes
    date;       April 10, 2015
    
    The push and pull instruction for the stack. This will store
    or load register values from memory.
*/

#include <stdint.h>

#include "registers.h"
#include "operations.h"


void
pushpull(uint16_t inst, registers *reg, void *memory)
{
    /*
     * if the PP_OP_L bit is set, load the stack into
     * the registers
     */
    if(PP_PUSH(inst)) {
        /*
         * High or low registers
         */
        
        /*
         * check if pull the program counter
         */
    }
    /*
     * If the PP_OP_L isn't set, push the registers onto
     * the stack.
     */
    else {
        /*
         * High or low registers
         */
        
        /*
         * check if push the link register
         */
        
    }
    return;
}
