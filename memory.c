#include <stdio.h>
#include "memory.h"

void* reallocate(void* ptr, size_t size)
{
    if(size == 0) 
    {
        free(ptr);
        return NULL;
    }
    void* result = realloc(NULL, size);
    if(!result) 
    {
        perror("Error");
        exit(69);
    }
    return result;
}
