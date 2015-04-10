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

#define LOW_REG     7   /* max for the low registers  */
#define HIGH_REG    8   /* min for the high registers */

void
pushpull(uint16_t inst, registers *reg, void *memory)
{
    /*
     * if the PP_OP_L bit is set, load the stack into
     * the registers
     */
    if(PP_PUSH(inst)) {
        if(PP_HIGH(inst)) {     /* use HIGH_REG and count to REG_FILE_S */

        }
        else {                  /* use 0 and count to REG_LOW */

        }
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

/*
 * Pushes a full register into memory.
 */
void
push(uint16_t inst, registers *reg, void *memory)
{

    return;
}

/*
 * Pulls a full register's worth from memory.
 */
void
pull(uint16_t inst, registers *reg, void *memory)
{

    return;
}
