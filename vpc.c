/*
    vpc is a virtual memory program.

    author:     Dave Smith-Hayes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_MEMORY    16000U  /*  16 kB */
#define INPUT_BUFFER    256     /* 256  B */ 
#define MENU_INPUT_SIZE 3       /*   3  B */

/* Function prototypes */
void display_help();
void write_file(void *memory);
int  load_file(void *memory, unsigned int max);

/* Entry point */
int main(int argc, char *argv[])
{
    char selection;
    static char memory[TOTAL_MEMORY];
    int err;
    
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
                if((err = load_file(memory, TOTAL_MEMORY)) > 0)
                    fprintf(stdout, "file loaded.\n");
                else
                    fprintf(stdout, "error loading file: %d\n", err);
                break;
            
            case 'w':
                write_file(memory);
                break;
            
            case '?':
            case 'h':
                display_help();
                break;
        }
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
    This routine will write a file to the buffered memory.
*/
void write_file(void *memory) 
{ 
    int size;
    char file_name[INPUT_BUFFER];
    FILE *f;

    /* Get the user to input a new file name. */
    fprintf(stdout, "name of file: ");
    fgets(file_name, INPUT_BUFFER, stdin);
    
    file_name[strlen(file_name) - 1] = '\0';
    
    if((f = fopen((const char*) file_name, "w+")) == NULL) {
        fprintf(stdout, "error opening file to write.");
        exit(1);
    }
    
    /* Ask for how many bytes to write. */
    fprintf(stdout, "Number of bytes to write: ");
    fscanf(stdin, "%d", &size);    

    if(size > TOTAL_MEMORY)
        size = TOTAL_MEMORY;
    
    /* actually write the memory to a file */
    if(fwrite(memory, 1, size, f) > 0)
        fprintf(stdout, "write file successful.\n");
    else
        fprintf(stdout, "error writing file.\n");
    
    fclose(f);
}

/*
    This routine will load a file into the buffered memory, it will
    return the size of the file loaded.
    
    errors:
        -1:     error opening the file
        -2:     error finding the size of the file
        -3:     error reading the file into the virtual memory
*/
int load_file(void *memory, unsigned int max)
{
    char file_name[INPUT_BUFFER];       /* user given */
    FILE *f;                            /* the actual file */
    const char *mode = "r";             /* change this? */
    unsigned int size;
    
    fprintf(stdout, "file: ");
    fgets(file_name, INPUT_BUFFER, stdin);
    
    file_name[strlen(file_name) - 1] = '\0';
    
    /* -1 on failure to open the file */
    if((f = fopen((const char *)file_name, mode)) == NULL)
        return -1;
    
    /* -2 on failure to seek to the end */
    if(fseek(f, 0, SEEK_END) == 0)
        size = ftell(f);
    else
        return -2;
    
    if(size > max) {
        fprintf(stdout, "file truncated...\n");
        size = max;
    }
    
    rewind(f);
    
    /* -3 means it didn't read shit. */
    if(fgets(memory, size, f) == NULL) {
        fclose(f);
        return -3;
    }
    
    fclose(f);
    return size;
}
