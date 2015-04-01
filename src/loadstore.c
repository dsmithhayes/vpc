/*
    file:       loadstore.c
    author:     Dave Smith-Hayes
    date:       March 31, 2015
    
    The function written here will perform the appropriate load or
    store operation.
*/

#include "registers.h"
#include "operations.h"

void
loadstore(uint16_t inst, registers *reg, void *memory)
{
    uint8_t rn = RN(inst);
    uint8_t rd = RN(inst);
    
    if(IS_LS_LOAD(inst)) {  /* load transaction */
        if(IS_LS_WORD(inst)) {

        }
        else {

        }
    }
    else {                  /* store transation */
        if(IS_LS_WORD(inst)) {

        }
        else {

        }
    }
    
    return;
}
