/*
    file:       loadstore.c
    author:     Dave Smith-Hayes
    date:       March 31, 2015
    
    The function written here will perform the appropriate load or
    store operation.
*/

#include "registers.h"
#include "operations.h"

#define BYTE        8
#define BYTE_MASK   0x000F

#define BYTE_1(x)   (BYTE_MASK & x)
#define BYTE_2(x)   ((BYTE_MASK & x) >> BYTE)
#define BYTE_3(x)   ((BYTE_MASK & x) >> (BYTE * 2))
#define BYTE_4(x)   ((BYTE_MASK & x) >> (BYTE * 3))

void
loadstore(uint16_t inst, registers *reg, void *memory)
{
    uint8_t rn = RN(inst);
    uint8_t rd = RN(inst);

    reg->alu = 0;
    reg->mbr = 0;
    
    if(IS_LS_LOAD(inst)) {  /* load transaction */
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
    else {                  /* store transation */
        if(IS_LS_DWORD(inst)) {
            *((uint8_t *) memory + (rn++)) = BYTE_1(reg->file[rd]);
            *((uint8_t *) memory + (rn++)) = BYTE_2(reg->file[rd]);
            *((uint8_t *) memory + (rn++)) = BYTE_3(reg->file[rd]);
            *((uint8_t *) memory + rn) = BYTE_4(reg->file[rd]);
        }
        else
            *((uint8_t *) memory + rn) =
                    (uint8_t) (reg->file[rd] & BYTE_MASK);
    }
    
    return;
}
