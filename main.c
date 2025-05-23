#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chunk.h"

char* readfile(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if(!file)
    {
        perror("Error");
        exit(69);
    }
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);
    char* buffer = (char*) malloc(file_size + 1);
    if(!buffer)
    {
        perror("Error");
        fclose(file);
        exit(69);
    }
    size_t num_of_readb = fread(buffer, sizeof(char), file_size, file);
    if(num_of_readb != file_size)
    {
        free(buffer);
        fclose(file);
        fprintf(stderr, "Error Could not read file. Expected %zu got %zu\n",
                file_size, num_of_readb);
        exit(69);
    }
    buffer[file_size] = '\0';
    fclose(file);
    return buffer;
}

void repl(void)
{
    char buffer[1024] = {0};
    while(1)
    {
        printf(">> ");
        if(!fgets(buffer, sizeof(buffer), stdin))
        {
            break;
        }
    }
}

void print_chunk(Chunk *chunk)
{
    for(size_t i = 0; i < chunk->len; ++i)
    {
        printf("code -> %d\n", chunk->codes[i]);
    }
}

int main(int argc, char* argv[])
{

    Chunk chunk;
    init_chunk(&chunk);
    write_chunk(&chunk, OP_ADD);
    print_chunk(&chunk);

    return 0;

    if(argc == 1) 
    {
        repl();
    } else if(argc == 2) 
    {
        char* source = readfile(argv[1]);
        printf("%s\n", source);
        free(source);
    }
    return 0;
}

