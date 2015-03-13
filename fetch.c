/*
    file:   fetch.c
    author: Dave Smith-Hayes
    date:   Mar 12, 2015

    Fetches the next instruction from the memory.
*/

#include "vpc.h"

void
fetch()
{
	mra = registers[PC];
	mbr = memory[mra];
	
	
}
