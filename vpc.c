/*
    file:   load_file.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    this is the entry point of the program.
*/

#include "vpc.h"

/***************/
/* Entry point */
/***************/

int 
main(int argc, char *argv[])
{
    char selection;
    int size;                    /* result of load_file(); */
    unsigned int offset, length; /* for user input */

    
    /* Zero all of the registers */
    zero();


    /*
     * TODO: check if there is an argument,
     * see if its a file, open it.
     */

    
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
                if((size = loadf((void *) memory, TOTAL_MEMORY)) > 0)
                    fprintf(stdout, 
                            "file loaded. 0x%X (%d) bytes read.\n", 
                            size, size);
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


/**************************/
/* Functions and routines */
/**************************/

void
help()
{
    fprintf(stdout, "All number input should be in UPPER CASE HEX\n");
    fprintf(stdout, "Using lowercase will yield unfavourable results");

    fprintf(stdout, "d\tdump memory\n");
    fprintf(stdout, "g\tgo - run the program\n");
    fprintf(stdout, "l\tload a file into memory\n");
    fprintf(stdout, "m\tmemory modify\n");
    fprintf(stdout, "q\tquit\n");
    fprintf(stdout, "r\tdisplay registers\n");
    fprintf(stdout, "t\ttrace - execute one instruction\n");
    fprintf(stdout, "w\twrite file\n");
    fprintf(stdout, "z\treset all registers to 0\n");
    fprintf(stdout, "?, h\tdisplay this menu\n\n");
}
