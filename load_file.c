#include "vpc.h"

/*
    This routine will load a file into the buffered memory, it will
    return the size of the file loaded.
    
    errors:
        -1:     error opening the file
        -2:     error finding the size of the file
        -3:     error reading the file into the virtual memory
*/
int 
load_file(void *memory, unsigned int max)
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
