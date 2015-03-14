/*
    file:   load_file.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    this is the entry point of the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vpc.h"
#include "registers.h"
#include "interface.h"


/********************/
/* Global variables */
/********************/

/* 'vpc.h' */
unsigned char memory[TOTAL_MEMORY] = { (char) 0 };

/* 'registers.h' */
unsigned long registers[REG_FILE_S] = { 0 };
unsigned long ccr = 0;          /* Sign, Zero, Carry flags  */
unsigned long mbr = 0;          /* memory buffer register   */
unsigned long mar = 0;          /* memory address register  */
unsigned long ir  = 0;          /* instruction register     */
unsigned short ir_flag = 0;     /* 0 = IR0, 1 = IR1         */
unsigned short stop_flag = 0;   /* 1 = stop!, 0 = continue  */

/* 'interface.h' */

/***************/
/* Entry point */
/***************/

int 
main(int argc, char *argv[])
{
    char selection;
    int file_size;               /* result of load_file();   */
    unsigned int offset, length; /* for user input           */
    char *file_name;             /* in case file name passed */

    /* Zero all of the registers */
    zero();

    /*
     * TODO: check if there is an argument,
     * see if its a file, open it.
     */
    if(argc > 1) {
        /* load the file */

        /* announce success or failure on loading */
    }

    
    fprintf(stdout, "vpc, by: Dave Smith-Hayes\n");
    fprintf(stdout, "Type '?', 'H' or 'h' for a list of commands.\n");

    
    /* main program loop */
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
                if((file_size = loadf((void *) memory, TOTAL_MEMORY)) > 0)
                    fprintf(stdout,
                            "file loaded. 0x%X (%d) bytes read.\n", 
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
                fscanf(stdin, "%X", &offset);
                
                fprintf(stdout, "length> ");
                fscanf(stdin, "%X", &length);
                
                /* stop unreasonable numbers */
                offset = (offset >= TOTAL_MEMORY) 
                        ? 0 : offset;
                
                length = (length > (TOTAL_MEMORY - offset))
                        ? (TOTAL_MEMORY - offset) : length;
                
                dumpmem((void *) memory, offset, length);
                
                /* flush the '\n' */
                getchar();
                break;

            
            case 'm':   /* modify the memory */
            case 'M':
                fprintf(stdout, "offset> ");
                fscanf(stdin, "%X", &offset);
                
                modmem((void *) memory, offset);
                break;

            
            case 'r':   /* displays registers */
            case 'R':
                dumpreg();
                break;

            
            case 'z':   /* sets registers to zero */
            case 'Z':
                fprintf(stdout, "Setting all registers to 0.\n");
                zero();
                break;

            
            case 't':   /* trace the program */
            case 'T':
                trace();
                break;

            
            case '?':   /* display the help */
            case 'h':
            case 'H':
                help();
                break;

            
            default:
                fprintf(
                    stderr,
                    "This feature has not been implemented yet."
                );
                break;
        }
        
        fprintf(stdout, "\n");
    }
    
    return 0;
}
