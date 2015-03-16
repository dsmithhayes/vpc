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


/******************************/
/* The memory! The registers! */
/******************************/

unsigned char memory[TOTAL_MEMORY] = { (char) 0 };
struct registers reg;

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
    zero(&reg);

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
