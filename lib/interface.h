#ifndef INTERFACE_H
#define INTERFACE_H

/*
    Definitions and prototypes for the user interface.

    file:       interface.h
    author:     Dave Smith-Hayes
    date:       March 13, 2015
*/

#define INPUT_BUFFER    0xFF    /* 255B input for strings     */
#define HEX_INPUT       4       /* 4B for (hex) string values */
#define OUTPUT_MASK     0xFF
#define ROW_LENGTH      0x10    /* for the memory dump rows */

/* Display the usage help. */
void help();

#endif
