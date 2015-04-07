/*
    Performs the immediate instruction passed to the function.
    Basically everything is done within the big ass switch statement.
    
    file:       immediate.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "registers.h"
#include "operations.h"

/*
 * Monolithic function that performs the necessary immediate operation
 * to the data in register Rd.
 */
void
immediate(uint16_t inst, registers *reg)
{
    uint16_t opcode = IMM_GET_OPCODE(inst);
    uint8_t rd = RD(inst);
    uint16_t imm = IMM(inst);

    /*
     * Check which immediate instruction is given.
     */
    switch(opcode) {
        case MOV_IMM:
            reg->alu = imm;
            reg->file[rd] = reg->alu;
            break;

        case CMP_IMM:
            reg->alu = reg->file[rd] & ~imm + 1;
            break;

        case ADD_IMM:
            reg->alu = reg->file[rd] + imm;
            reg->file[rd] = reg->alu;
            break;
    
        case SUB_IMM:
            reg->alu = reg->file[rd] & ~imm + 1;
            reg->file[rd] = reg->alu;
            break;
    }

    return;
}
