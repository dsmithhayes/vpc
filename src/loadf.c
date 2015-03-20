/*
    file:   loadf.c
    author: Dave Smith-Hayes
    date:   February 13th, 2015

    This routine will load a file into the buffered memory, it will
    return the size of the file loaded.
    
    returns errno of appropriate failure, or the size of he file.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>    
#include "vpc.h"
#include "interface.h"

int 
loadf(void *memory, uint16_t max)
{
    char file_name[INPUT_BUFFER];   /* user given */
    FILE *f;                        /* the actual file */
    const char *mode = "rb";
    uint16_t size;
    
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
    
    return fread(memory, sizeof(uint8_t), size, f);
}
