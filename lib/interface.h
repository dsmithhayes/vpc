#ifndef INTERFACE_H
#define INTERFACE_H

/*
    Definitions and prototypes for the user interface. Most of
    these definitions help format the output data.

    file:       interface.h
    author:     Dave Smith-Hayes
    date:       March 13, 2015
*/

/*******************/
/* System Includes */
/*******************/

#include <stdint.h>


/**************************/
/* Definitions for Output */
/**************************/

#define INPUT_BUFFER    0xFF    /* 255B input for strings     */
#define HEX_INPUT       4       /* 4B for (hex) string values */
#define OUTPUT_MASK     0xFF
#define ROW_LENGTH      0x10    /* for the memory dump rows */


/***********************/
/* Function Prototypes */
/***********************/

/* Display the usage help. */
void help();

#endif /* INTERFACE_H */
