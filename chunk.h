#ifndef CHUNK_H
#define CHUNK_H
#include <stdint.h>
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_ADD,
    OP_DIV,
    OP_MULT,
    OP_SUB,
    OP_RETURN
} OP_CODE;

typedef uint8_t Word;

typedef struct {
    unsigned int len;
    unsigned int capacity;
    int* lines;
    Word* codes;
    ValueArray constants;
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, Word op);
int add_constant(Chunk* chunk, Value value);
void free_chunk(Chunk* chunk);

#endif
