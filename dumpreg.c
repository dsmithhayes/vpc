/*
    file:   dumpreg.c
    author: Dave Smith-Hayes
    date:   February 27th, 2015

    Displays the contents of each register.
*/
#include "vpc.h"


void
dumpreg()
{
    unsigned short i = 0;
    
    while(i < TOTAL_REG) {
        
        fprintf(
            stdout,
            "R%2d: 0x%08lX ",
            i,
            registers[i++]
        );

        if(i == SP)
            break;

        if(i % 4 == 0)
            fprintf(stdout, "\n");
    }
    
    fprintf(stdout, " SP: 0x%08lX ", registers[SP]);
    fprintf(stdout, " LR: 0x%08lX ", registers[LR]);
    fprintf(stdout, " PC: 0x%08lX\n", registers[PC]);
    
    fprintf(stdout, "\n");
    
    /* check the CCR */
    fprintf(stdout, "CCR: %d%d%d (sign, zero, carry)\n",
        (ccr & SIGN) ? 1 : 0,
        (ccr & ZERO) ? 1 : 0,
        (ccr & CARRY) ? 1 : 0
    );

    fprintf(stdout, "MBR: 0x%08lX\n", mbr);
    fprintf(stdout, "MAR: 0x%08lX\n", mar);
    fprintf(stdout, "IR0: 0x%04X\n", ir0(ir));
    fprintf(stdout, "IR1: 0x%04X\n", ir0(ir1(ir)));

    fprintf(stdout, "\n");
    fprintf(stdout, "Stop Flag: %d\n", stop_flag ? 1 : 0);
    fprintf(stdout, "Active IR: %d\n", ir_flag ? 1 : 0);
    
    return;
}

unsigned int
ir0(unsigned long in) { return in >> 0x10; }

unsigned int
ir1(unsigned long in) { return (in << 0x10) >> 0x10; }
