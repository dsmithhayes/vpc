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
 *
 * the BYTE_N(x) macros are in 'registers.h' and define how to
 * break 32bites into 4 seperate bytes.
 */
void
push(uint32_t reg, uint32_t *mar, void *memory) 
{
    *((uint8_t *) memory + (*mar++)) = BYTE_1(reg);
    *((uint8_t *) memory + (*mar++)) = BYTE_2(reg);
    *((uint8_t *) memory + (*mar++)) = BYTE_3(reg);
    *((uint8_t *) memory + *mar) = BYTE_4(reg);

    return;
}

/*
 * Pulls a full register's worth from memory.
 */
void
pull(uint32_t *reg, uint32_t *mar, void *memory)
{
    *reg = *((uint8_t *) memory + (*mar++));
    *reg = (*reg << BYTE);

    *reg |= *((uint8_t *) memory + (*mar++));
    *reg = (*reg << BYTE);

    *reg |= *((uint8_t *) memory + (*mar++));
    *reg = (*reg << BYTE);

    *reg = *((uint8_t *) memory + (*mar++));

    return;
}
