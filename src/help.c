/*
    file:       help.c
    author:     Dave Smith-Hayes
    date:       March 13, 2015
    
    Defines the function that displays the help menu. That's it.
*/

#include <stdio.h>
#include "interface.h"

void
help()
{
    fprintf(stdout, "All number input should be in UPPER CASE HEX\n");
    fprintf(stdout, "Using lowercase could yield to unfavourable results\n\n");

    fprintf(stdout, "d\tdump memory\n");
    fprintf(stdout, "g\tgo - run the program\n");
    fprintf(stdout, "l\tload a file into memory\n");
    fprintf(stdout, "m\tmemory modify\n");
    fprintf(stdout, "q\tquit\n");
    fprintf(stdout, "r\tdisplay registers\n");
    fprintf(stdout, "t\ttrace - execute one instruction\n");
    fprintf(stdout, "w\twrite file\n");
    fprintf(stdout, "z\treset all registers to 0\n");
    fprintf(stdout, "?, h\tdisplay this menu\n");

    return;
}
