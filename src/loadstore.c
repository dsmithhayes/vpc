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
    
    /*
     * LOAD
     */
    if(IS_LS_LOAD(inst)) {
        if(IS_LS_DWORD(inst)) {
            reg->alu = *((uint8_t *) memory + (rn++));
            reg->alu = (reg->alu << BYTE);
            
            reg->alu |= *((uint8_t *) memory + (rn++));
            reg->alu = (reg->alu << BYTE);
            
            reg->alu |= *((uint8_t *) memory + (rn++));
            reg->alu = (reg->alu << BYTE);
            
            reg->alu |= *((uint8_t *) memory + (rn++));
        }
        else
            reg->alu = *((uint8_t *) memory + rn);

        reg->file[rd] = reg->alu;
    }
    /*
     * STORE
     */
    else {
        if(IS_LS_DWORD(inst)) {
            reg->mbr = reg->file[rd];
            
            *((uint8_t *) memory + (rn++)) = BYTE_4(reg->mbr);
            *((uint8_t *) memory + (rn++)) = BYTE_3(reg->mbr);
            *((uint8_t *) memory + (rn++)) = BYTE_2(reg->mbr);
            *((uint8_t *) memory + rn) = BYTE_1(reg->mbr);
        }
        else
            *((uint8_t *) memory + rn) =
                    (uint8_t) (reg->file[rd] & BYTE_MASK);
    }
    
    return;
}
