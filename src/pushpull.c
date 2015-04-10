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
    uint8_t i, j;
    uint8_t reg_set[] = {
        PP_REG_1, PP_REG_2, PP_REG_3, PP_REG_4,
        PP_REG_5, PP_REG_6, PP_REG_7, PP_REG_8
    };
    uint8_t set_reg = PP_GET_REG(inst);

    /*
     * Set the Memory Address Buffer to the Stack Pointer
     */
    reg->mar = reg->file[SP];
    
    /*
     * if the PP_OP_L bit is set, load the stack into
     * the registers
     */
    if(PP_PUSH(inst)) {
        /*
         * pull the Program Counter
         */
        if(PP_EXTRA(inst))
            pull(&(reg->file[PC]), &(reg->mar), memory);

        /*
         * If its the high part of the registers
         */
        if(PP_HIGH(inst)) {
            for(i = HIGH_REG, j = 0; i < REG_FILE_S; i++)
                if((reg_set[j++] & set_reg))
                    push(reg->file[i], &(reg->mar), memory);
        }
        else {
            for(i = 0; i <= LOW_REG; i++)
                if((reg_set[i] & set_reg))
                    push(reg->file[i], &(reg->mar), memory);
        }
    }
    /*
     * If the PP_OP_L isn't set, push the registers onto
     * the stack.
     */
    else {
        /*
         * Push the Link Register
         */
        if(PP_EXTRA(inst))
            push(reg->file[LR], &(reg->mar), memory);

        /*
         * If its the high part of the registers
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
