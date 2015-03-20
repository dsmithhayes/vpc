/*
    file:   dumpreg.c
    author: Dave Smith-Hayes
    date:   February 27th, 2015

    Displays the contents of each register.
*/

#include <stdio.h>
#include "registers.h"

void
dumpreg(registers reg)
{
    unsigned short i = 0;

    /* Display the registers in a 4x4 grid */
    while(i < REG_FILE_S) {
        
        fprintf(stdout, "R%2d: 0x%08X ", i, reg.file[i++]);

        if(i == SP)
            break;

        if(i % 4 == 0)
            fprintf(stdout, "\n");
    }

    /* Special value registers */
    fprintf(stdout, " SP: 0x%08X ",  reg.file[SP]);
    fprintf(stdout, " LR: 0x%08X ",  reg.file[LR]);
    fprintf(stdout, " PC: 0x%08X\n", reg.file[PC]);
    
    fprintf(stdout, "\n");
    
    /* check the CCR */
    fprintf(stdout, "CCR: %d%d%d (sign, zero, carry)\n",
        (reg.ccr & SIGN)  ? 1 : 0,
        (reg.ccr & ZERO)  ? 1 : 0,
        (reg.ccr & CARRY) ? 1 : 0
    );

    fprintf(stdout, "MBR: 0x%08X\n", reg.mbr);
    fprintf(stdout, "MAR: 0x%08X\n", reg.mar);
    fprintf(stdout, "IR0: 0x%04X\n", ir0(reg.ir));
    fprintf(stdout, "IR1: 0x%04X\n", ir1(reg.ir));

    fprintf(stdout, "\n");
    fprintf(stdout, "Stop Flag: %d\n", reg.stp_flg ? 1 : 0);
    fprintf(stdout, "Active IR: %d\n", reg.ir_flg ? 1 : 0);
    
    fprintf(stdout, "\n");

    return;
}

uint16_t
ir0(uint32_t in)
{
    return in >> INS_BIT_S;
}

uint16_t
ir1(uint32_t in)
{
    unsigned int tmp = in << INS_BIT_S;
    return ir0(tmp);
}
