#ifndef VM_H
#define VM_H

#include "chunk.h"

#define STACK_SIZE 1024

typedef struct {
    Chunk* chunk;
    Value stack[STACK_SIZE];
    Value* stack_top;
    Word* ip;
} Vm;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILATION_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void init_vm(void);
void free_vm(void);

InterpretResult interpret(Chunk* chunk);
#endif
