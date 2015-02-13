/*
    file:   load_file.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    this is the entry point of the program.
*/

#include "vpc.h"

/* Entry point */

int 
main(int argc, char *argv[])
{
    char selection;
    static char memory[TOTAL_MEMORY];
    int file_size;   /* result of load_file(); */
    
    fprintf(stdout, "vpc, by: Dave Smith-Hayes\n");
    fprintf(stdout, "Type '?' or 'h' for a list of commands.\n");
    
    /* main program loop */
    while(1) {
        fprintf(stdout, "> ");
        fgets(&selection, MENU_INPUT_SIZE, stdin);
        
        switch(selection) {
            case 'q':
            case 'Q':
                exit(0);
                break;
            
            case 'l':   /* load a file */
            case 'L':
                if((file_size = load_file(memory, TOTAL_MEMORY)) > 0)
                    fprintf(stdout, 
                            "file loaded. %d (0x%x) bytes read.\n", 
                            file_size, file_size);
                else
                    perror("load_file: ");
                
                break;
            
            case 'w':   /* write the file */
            case 'W':
                write_file(memory);
                break;
            
            case 'd':   /* dump the memory */
            case 'D':
                
                break;
            
            case 'm':   /* modify the memory */
            case 'M':
                
                break;
            
            case '?':
            case 'h':
                display_help();
                break;
        }
    }
    
    return 0;
}
