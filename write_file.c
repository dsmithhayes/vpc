/*
    file:   load_file.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    this file defines the load_file() function.
*/

#include "vpc.h"

/*
    This routine will write a file to the buffered memory.
*/
void 
write_file(void *memory) 
{ 
    int size;
    unsigned int res;   /* result of fwrite */
    char file_name[INPUT_BUFFER];
    FILE *f;

    /* Get the user to input a new file name. */
    fprintf(stdout, "name of file> ");
    fgets(file_name, INPUT_BUFFER, stdin);
    
    file_name[strlen(file_name) - 1] = '\0';
    
    if((f = fopen((const char*) file_name, "w+")) == NULL) {
        fprintf(stdout, "error opening file to write.");
        return;
    }
    
    /* Ask for how many bytes to write. */
    fprintf(stdout, "Number of bytes to write (hex)> ");
    fscanf(stdin, "%x", &size);

    if(size > TOTAL_MEMORY)
        size = TOTAL_MEMORY;
    
    /* actually write the memory to a file */
    if((res = fwrite(memory, 1, size, f)) > 0)
        fprintf(stdout, "wrote %d bytes to file successfully.\n", res);
    else
        fprintf(stdout, "error writing file.\n");
    
    fclose(f);
    return;
}
