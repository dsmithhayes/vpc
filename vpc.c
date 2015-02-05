/*
    vpc is a virtual memory program.

    author:		Dave Smith-Hayes
*/
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_MEMORY    16000U	/* 16kB */

/* Function prototypes */
void display_help();
void get_input(char *in);
void write_file(void *memory);
int  load_file(void *memory, unsigned int max);

/* Entry point */
int main(int argc, char *argv[])
{
    /* Variables */
    char memory[TOTAL_MEMORY];
    char input;
    
    /* The menu and operations */
    fprintf(stdout, "'h' or '?' for help, 'q' to quit.\n");
    get_input(&input);
    
    while(1) {
        switch(input) {
            /* load the file */
            case 'l':
                
                break;
            
            /* write the file */    
            case 'w':
                
                break;
            
            /* display the help menu */
            case '?':
            case 'h':
                display_help();
                break;
        }
        
        if(input == 'q')
			break;
        
        get_input(&input);
    }
    
    return 0;
}

/*
    This routine will print all of the program's
    options onto the screen.
*/
void display_help()
{
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

/*
    this routine just captures the input
*/
void get_input(char *in)
{
    fprintf(stdout, "> ");
    *in = (int)fgetc(stdin);
}

/*
    This routine will write a file to the buffered
    memory.
*/
void write_file(void *memory)
{
    
}

/*
    This routine will load a file into
    the buffered memory.
*/
int load_file(void *memory, unsigned int max)
{
    static char *file_name;		/* user given */
    static FILE *f;				/* the actual file */
	static char *mode = "a+";	/* change this? */
    unsigned int size;
    
    fprintf(stdout, "file: ");
    fscanf(stdin, "%s", file_name);
    
    /* -1 on failure. */
    if((f = fopen(file_name, mode)) == NULL)
		return -1;
	
	size = ftell(f);
	
    if(size > max) {
		fprintf(stdout, "File truncated...\n");
		size = max;
	}
	
	return (int) fread(memory, sizeof(char), size, f);
}
