/*
    The main entry point and where the memory and registers are
    actually declared.

    file:       main.c
    author:     Dave Smith-Hayes
    date:       March 16, 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vpc.h"
#include "registers.h"
#include "operations.h"
#include "interface.h"


/******************************/
/* The memory! The registers! */
/******************************/

uint8_t memory[TOTAL_MEMORY] = { 0 };
registers reg;


/***************/
/* Entry point */
/***************/

int 
main(int argc, char *argv[])
{
    char selection;
    unsigned int file_size;     /* result of load_file();   */
    uint16_t offset, length;    /* for user input           */


    /* Zero all of the registers */
    zero(&reg);
    
    /* Introduction, I WROTE THIS PROGRAM MYSELF */
    fprintf(stdout, "vpc, by: Dave Smith-Hayes\n");
    fprintf(stdout, "Type '?', 'H' or 'h' for a list of commands.\n");
    
    
    /*
     * main program loop
     */
    while(1) {          /* bold statement assuming numbers exist! */
        fprintf(stdout, "option> ");
        selection = getchar();
        while(getchar() != '\n');
        
        switch(selection) {
            case 'q':
            case 'Q':
                exit(0);
                break;

            
            case 'l':   /* load a file */
            case 'L':
                file_size = loadf((void *) memory, TOTAL_MEMORY);
                
                if(file_size > 0)
                    fprintf(stdout,
                            "File loaded. 0x%04X (%d) bytes read.\n", 
                            file_size, file_size);
                else
                    perror("loadf");
                break;

            
            case 'w':   /* write the file */
            case 'W':
                writef((void *) memory);
                
                /* flush the '\n' */
                getchar();
                break;

            
            case 'd':   /* dump the memory */
            case 'D':
                fprintf(stdout, "offset> ");
                fscanf(stdin, "%X", (unsigned int *) &offset);
                
                fprintf(stdout, "length> ");
                fscanf(stdin, "%X", (unsigned int *) &length);

                offset &= (TOTAL_MEMORY - 1);
                
                /*
                 * Windows does weird things if its 0 so 0 defaults
                 * to one line.
                 */
                length = (((length > (TOTAL_MEMORY - offset))
                        ? (TOTAL_MEMORY - offset) : length) == 0)
                                ? ROW_LENGTH : length;
                
                dumpmem((void *) memory, offset, length);
                
                /* flush the '\n' */
                getchar();
                break;

            
            case 'm':   /* modify the memory */
            case 'M':
                fprintf(stdout, "offset> ");
                fscanf(stdin, "%X", (unsigned int *) &offset);
                
                modmem((void *) memory, offset);
                break;

            
            case 'r':   /* displays registers */
            case 'R':
                dumpreg(reg);
                break;

            
            case 'z':   /* sets registers to zero */
            case 'Z':
                fprintf(stdout, "Setting all registers to 0.\n");
                zero(&reg);
                break;

            
            case 't':   /* trace the program */
            case 'T':
                trace((void *) memory, &reg);

                getchar();
                break;

            case 'g':
            case 'G':
                go(memory, &reg);
                break;
            
            case '?':   /* display the help */
            case 'h':
            case 'H':
                help();
                break;

            
            default:
                fprintf(stderr,
                        "This feature has not been implemented yet.");
                break;
        }
        
        fprintf(stdout, "\n");
    }
    
    return 0;
}
