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
    uint8_t i = 0;

    /*
     * Display the registers in a 4x4 grid
     */
    while(i < REG_FILE_S) {
        
        fprintf(stdout, "R%02d: 0x%08X ", i, reg.file[i++]);

        if(i == SP) /* just to label the SP, LR, and PC */
            break;

        if(i % 4 == 0)
            fprintf(stdout, "\n");
    }

    /* 
     * Special value registers 
     */
    fprintf(stdout, " SP: 0x%08X ",  reg.file[SP]);
    fprintf(stdout, " LR: 0x%08X ",  reg.file[LR]);
    fprintf(stdout, " PC: 0x%08X\n", reg.file[PC]);
    
    fprintf(stdout, "\n");
    
    /* 
     * check the CCR 
     */
    fprintf(stdout, "CCR: %d%d%d (sign, zero, carry)\n",
        IS_CARRY_SET(reg.ccr),
        IS_ZERO_SET(reg.ccr),
        IS_SIGN_SET(reg.ccr)
    );

    /*
     * Memory Buffer Register, Memory Address Register, and the value
     * of each instruction register
     */
    fprintf(stdout, "MBR: 0x%08X\n", reg.mbr);
    fprintf(stdout, "MAR: 0x%08X\n", reg.mar);
    fprintf(stdout, "IR0: 0x%04X\n", IR0(reg.ir));
    fprintf(stdout, "IR1: 0x%04X\n", IR1(reg.ir));

    fprintf(stdout, "\n");
    fprintf(stdout, "Stop Flag: %d\n", IS_STOP_SET(reg.stop_flag));
    fprintf(stdout, "Active IR: %d\n", WHICH_IR(reg.ir_flag));

    return;
}
