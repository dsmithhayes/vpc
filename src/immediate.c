/*
    Performs the immediate instruction passed to the function.
    Basically everything is done within the big ass switch statement.
    
    file:       immediate.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

void
immediate(
        unsigned int mask,
        unsigned int inst,
        registers *reg)
{
    unsigned int rd = get_rd(inst);
    
    switch(mask) {
        case MOV_IMM:
            reg->file[rd] = inst & IMM_VAL;
            break;

        case CMP_IMM:

            break;

        case ADD_IMM:
            
            break;

        case SUB_IMM:

            break;

        default:
            return;
    }

    return;
}
