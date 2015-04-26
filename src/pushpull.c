/*
    file:       pushpull.c
    author:     Dave Smith-Hayes
    date;       April 10, 2015
    
    The push and pull instruction for the stack. This will store or 
    load register values from memory.
*/

#include <stdint.h>
#include "registers.h"
#include "operations.h"

#define LOW_REG     7   /* max for the low registers  */
#define HIGH_REG    8   /* min for the high registers */


void
pushpull(uint16_t inst, registers *reg, void *memory) 
{
    uint8_t i, j;               /* counters */
    uint8_t reg_mask_set[] = {  /* the masks for the 8 registers */
        PP_REG_1, PP_REG_2,
        PP_REG_3, PP_REG_4,
        PP_REG_5, PP_REG_6,
        PP_REG_7, PP_REG_8
    };
    uint8_t set_reg = PP_GET_REG(inst); /* the registers */
    
    /* PUSH
     * 
     * if the PP_OP_L bit is set, load the stack into the registers
     */
    if(PP_PUSH(inst)) {
        /*
         * Push the Link Register
         */
        if(PP_EXTRA(inst))
            push(reg->file[LR], &(reg->mar), memory);
        
        /*
         * push the higher registers
         */
        if(PP_HIGH(inst))
            for(i = HIGH_REG, j = 0; i < REG_FILE_S; i++)
                if(reg_mask_set[j++] & set_reg) {
                    reg->file[SP] = (reg->file[SP] - REG_SIZE);
                    push(reg->file[i], &(reg->mar), memory);
                }
        /*
         * push the lower registers
         */
        else
            for(i = 0; i <= LOW_REG; i++)
                if(reg_mask_set[i] & set_reg) {
                    reg->file[SP] = (reg->file[SP] - REG_SIZE);
                    push(reg->file[i], &(reg->mar), memory);
                }
    }
    /*
     * PULL
     * 
     * If the PP_OP_L isn't set, push the registers onto the stack.
     */
    else {
        /*
         * If its the high part of the registers
         */
        if(PP_HIGH(inst))
            for(i = HIGH_REG, j = REG_FILE_S; i >= HIGH_REG; i--)
                if(reg_mask_set[j--] & set_reg) {
                    pull(&(reg->mbr), &(reg->mar), memory);
                    reg->file[SP] = (reg->file[SP] + REG_SIZE);
                }
        /*
         * The low part of the registers
         */
        else
            for(i = LOW_REG; i <= 0; i--)
                if(reg_mask_set[i] & set_reg) {
                    pull(&(reg->mbr), &(reg->mar), memory);
                    reg->file[SP] = (reg->file[SP] + REG_SIZE);
                }

        /*
         * pull the Program Counter
         */
        if(PP_EXTRA(inst))
            pull(&(reg->file[PC]), &(reg->mar), memory);
    }
    
    return;
}

/*
 * Pushes a full register into memory.
 *
 * the BYTE_N(x) macros are in 'inc/registers.h' and define how to
 * break 32bits into 4 seperate bytes. The push takes the most
 * significant byte first and pushes that.
 */
void
push(uint32_t reg, uint32_t *mar, void *memory) 
{
    *((uint8_t *) memory + (*mar++)) = BYTE_4(reg);     /* MSB first */
    *((uint8_t *) memory + (*mar++)) = BYTE_3(reg);
    *((uint8_t *) memory + (*mar++)) = BYTE_2(reg);
    *((uint8_t *) memory + *mar) = BYTE_1(reg);         /* LSB last */

    return;
}

/*
 * Pulls a full register's worth from memory. The pull starts with 
 * the most significant byte and move on.
 */
void
pull(uint32_t *mbr, uint32_t *mar, void *memory)
{
    *mbr = *((uint8_t *) memory + (*mar)++);    /* MSByte */
    *mbr = (*mbr << BYTE);

    *mbr |= *((uint8_t *) memory + (*mar)++);
    *mbr = (*mbr << BYTE);

    *mbr |= *((uint8_t *) memory + (*mar)++);
    *mbr = (*mbr << BYTE);

    *mbr |= *((uint8_t *) memory + (*mar)++);   /* LSByte */

    return;
}
