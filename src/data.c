/*
    Performs a register to register operation.
    
    file:       data.c
    author:     Dave Smith-Hayes
    date:       March 26, 2015
*/

#include "registers.h"
#include "operations.h"

void
data(uint16_t mask, uint16_t inst, registers *reg)
{
    uint8_t rd = get_rd(inst);
    uint8_t rn = get_rn(inst);

    switch(mask) {
        
    }

    toggle_flg(INST_FLAG, (uint32_t) &(reg->ir_flag));
    
    return;
}
