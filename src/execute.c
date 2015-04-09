/*
    Executes the instruction given. First it decides which instruction
    it is, and then proceeds to perform the operation to the according
    registers within the opcode data.

    for each type of instruction type, there is a corresponding function
    with an obvious name. Immediate instructions is `immediate()`.
    
    file:       execute.c
    author:     Dave Smith-Hayes
    date:       March 26, 2015
*/

#include "registers.h"
#include "operations.h"

void
execute(uint16_t inst, registers *reg, void *memory)
{

    if(IS_IMM_INST(inst))
        immediate(inst, reg);
    
    if(IS_DAT_INST(inst))
        data(inst, reg);
    
    if(IS_LS_INST(inst))
        loadstore(inst, reg, memory);
    
    if(IS_STOP_INST(inst))
        set_reg_flag(STOP_FLAG, (uint32_t *) &(reg->stop_flag));

    toggle_reg_flag(INST_FLAG, (uint32_t *) &(reg->ir_flag));
    
    return;
}
