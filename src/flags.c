/*
    Functions in this file change the value of the flag that is
    passed to it.

    file:       flags.c
    author:     Dave Smith-Hayes
    date:       March 18, 2015
*/

#include "operations.h"

void
set_flg(unsigned short *flag)
{
    *flag = !*flag;
}
