/*
    Performs a register to register operation.
    
    file:       data.c
    author:     Dave Smith-Hayes
    date:       March 28, 2015
*/

#include "registers.h"
#include "operations.h"

void
data(uint16_t inst, registers *reg)
{
    uint8_t rd = get_rd(inst);
    uint8_t rn = get_rn(inst);
    uint8_t opcode = DAT_GET_OPCODE(inst);
    
    switch(opcode) {
        case ADD_DAT:
            reg->file[rd] += reg->file[rn];
            break;
        
    }
    
    return;
}
