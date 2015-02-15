/*
    file:   load_file.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015
    
    write_file will write the memory contents to a file.
*/

#include "vpc.h"

void 
write_file(void *memory) 
{ 
    unsigned int size;
    unsigned int res;   /* result of fwrite */
    char file_name[INPUT_BUFFER];
    FILE *f;

    /* Get the user to input a new file name. */
    fprintf(stdout, "filename> ");
    fgets(file_name, INPUT_BUFFER, stdin);
    
    file_name[strlen(file_name) - 1] = '\0';
    
    if((f = fopen((const char*) file_name, "wb")) == NULL) {
        perror("fopen");
        return;
    }
    
    /* Ask for how many bytes to write. */
    fprintf(stdout, "bytes to write (hex)> ");
    fscanf(stdin, "%X", &size);

    if(size > TOTAL_MEMORY)
        size = TOTAL_MEMORY;
    
    /* actually write the memory to a file */
    if((res = fwrite(memory, 1, size, f)) > 0)
        fprintf(stdout, "wrote %X (%d) bytes to file successfully.\n", 
                res, res);
    else
        perror("fwrite");
    
    fclose(f);
    return;
}
