/*
    file:   trace.c
    author: Dave Smith-Hayes
    date:   March 5th, 2015

    This file holds the trace() and fetch() functions.
*/

#include <stdio.h>
#include "vpc.h"
#include "registers.h"

void
trace()
{
    /* Basically just single step through the program */
    fetch((void *) memory);

    return;
}
