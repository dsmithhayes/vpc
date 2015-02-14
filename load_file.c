/*
    file:   load_file.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015

    This routine will load a file into the buffered memory, it will
    return the size of the file loaded.
    
    returns errno of appropriate failure, or the size of he file.

*/
    
#include "vpc.h"

int 
load_file(void *memory, unsigned int max)
{
    char file_name[INPUT_BUFFER];       /* user given */
    FILE *f;                            /* the actual file */
    const char *mode = "r";             /* change this? */
    unsigned int size;
    
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
    
    /* if it didn't read anything for some reason. */
    if(fgets((char *) memory, size, f) == NULL) {
        fclose(f);
        return errno;
    }
    
    fclose(f);
    return size;
}
