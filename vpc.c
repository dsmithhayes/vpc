#include "vpc.h"

/* Entry point */

int main(int argc, char *argv[])
{
    char selection;
    static char memory[TOTAL_MEMORY];
    int res;   /* result of load_file(); */
    
    fprintf(stdout, "vpc, by: Dave Smith-Hayes\n");
    fprintf(stdout, "Type '?' or 'h' for a list of commands.\n");
    
    while(1) {
        fprintf(stdout, "> ");
        fgets(&selection, MENU_INPUT_SIZE, stdin);
        
        switch(selection) {
            case 'q':
                exit(0);
                break;
            
            case 'l':
                if((res = load_file(memory, TOTAL_MEMORY)) > 0)
                    fprintf(stdout, 
                            "file loaded. %d bytes read.\n", res);
                else
                    fprintf(stdout, 
                            "error loading file: %d\n", res);
                break;
            
            case 'w':
                write_file(memory);
                break;
            
            case 'd':
            
                break;
            
            case 'm':
            
                break;
            
            case '?':
            case 'h':
                display_help();
                break;
        }
    }
    
    return 0;
}
