/*
    file:   loadf.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015

    This routine will load a file into the buffered memory, it will
    return the size of the file loaded.
    
    returns errno of appropriate failure, or the size of he file.

*/
    
#include "vpc.h"

int 
loadf(void *memory, unsigned int max)
{
    char file_name[INPUT_BUFFER];   /* user given */
    FILE *f;                        /* the actual file */
    const char *mode = "rb";        /* change this? */
    unsigned int size;
    char buffer;
    int i = 0;
    
    fprintf(stdout, "file> ");
    fgets(file_name, INPUT_BUFFER, stdin);
    
    file_name[strlen(file_name) - 1] = '\0';
    
    /* failure to open, happens when file doesn't exist. */
    if((f = fopen((const char *)file_name, mode)) == NULL)
        return errno;
    
    /* if for what ever reason seek() fails... */
    if(fseek(f, 0, SEEK_END) == 0)
        size = ftell(f);
    else
        return errno;
    
    if(size > max) {
        fprintf(stdout, "file truncated...\n");
        size = max;
    }
    
    rewind(f);
    
    return fread(memory, sizeof(char), size, f);
}
