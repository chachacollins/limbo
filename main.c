#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"


char* readfile(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if(!file)
    {
        perror("Error");
        exit(69);
    }
    fseek(file, 0, SEEK_END);
    size_t size_of_file = ftell(file);
    rewind(file);
    char* buffer = (char*) malloc(size_of_file + 1);
    if(!buffer)
    {
        perror("Error");
        fclose(file);
        exit(69);
    }
    size_t num_of_readb = fread(buffer, sizeof(char), size_of_file, file);
    if(num_of_readb != size_of_file)
    {
        free(buffer);
        fclose(file);
        fprintf(stderr, "Error Could not read file. Expected %zu got %zu\n",
                size_of_file, num_of_readb);
        exit(69);
    }
    buffer[size_of_file] = '\0';
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

int main(int argc, char* argv[])
{
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
