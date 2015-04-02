/*
    file:       loadstore.c
    author:     Dave Smith-Hayes
    date:       March 31, 2015
    
    The function written here will perform the appropriate load or
    store operation.
*/

#include "registers.h"
#include "operations.h"

#define BYTE   8


void
loadstore(uint16_t inst, registers *reg, void *memory)
{
    uint8_t _buf1, _buf2;
    uint8_t rn = RN(inst);
    uint8_t rd = RN(inst);

    reg->alu = 0;
    reg->mbr = 0;
    
    if(IS_LS_LOAD(inst)) {  /* load transaction */
        if(IS_LS_WORD(inst)) {
            reg->alu = *((uint8_t *) memory + (rn++));
            reg->alu = (reg->alu << BYTE);
            reg->alu += *((uint8_t *) memory + rn);
        }
        else
            reg->alu = *((uint8_t *) memory + rn);

        reg->file[rd] = reg->alu;
    }
    else {                  /* store transation */
        if(IS_LS_WORD(inst)) {
            
        }
        else {

        }
    }
    
    return;
}
