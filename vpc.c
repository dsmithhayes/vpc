/*
    file:   load_file.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    this is the entry point of the program.
*/

#include "vpc.h"

/* inline functions */

inline void 
display_help()
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

/* Entry point */

int 
main(int argc, char *argv[])
{
    char selection;
    static char memory[TOTAL_MEMORY];
    int file_size;   /* result of load_file(); */
    unsigned int offset, length;  /* for user input */
    
    fprintf(stdout, "vpc, by: Dave Smith-Hayes\n");
    fprintf(stdout, "Type '?' or 'h' for a list of commands.\n");
    
    /* main program loop */
    while(1) {
        fprintf(stdout, "option> ");
        selection = getchar();
        
        switch(selection) {
            case 'q':
            case 'Q':
                exit(0);
                break;
            
            case 'l':   /* load a file */
            case 'L':
                if((file_size = load_file(memory, TOTAL_MEMORY)) > 0)
                    fprintf(stdout, 
                            "file loaded. 0x%X (%d) bytes read.\n", 
                            file_size, file_size);
                else
                    perror("load_file");
                break;
            
            case 'w':   /* write the file */
            case 'W':
                write_file(memory);
                break;
            
            case 'd':   /* dump the memory */
            case 'D':
                fprintf(stdout, "Offset> ");
                fscanf(stdin, "%X", &offset);
                
                fprintf(stdout, "Length> ");
                fscanf(stdin, "%X", &length);
                
                /* start from beginning if the numbers are 
                   unreasonable. */
                offset = (offset > TOTAL_MEMORY) 
                        ? 0 : offset;
                
                length = (length > (TOTAL_MEMORY - offset))
                        ? 0x10 : length;
                
                dump_memory((void *) memory, offset, length);
                break;
            
            case 'm':   /* modify the memory */
            case 'M':
                fprintf(stdout, "Offset> ");
                fscanf(stdin, "%X", &offset);
                
                modify_memory(memory, offset);
                break;
            
            case '?':   /* display the help */
            case 'h':
                display_help();
                break;
        }
        
        /* flushes the '\n' in stdin */
        getchar();
    }
    
    return 0;
}
