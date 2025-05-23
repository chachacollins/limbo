#include "chunk.h"
#include "memory.h"

void init_chunk(Chunk* chunk)
{
    chunk->len = 0;
    chunk->capacity = 0;
    chunk->codes = NULL;
    chunk->lines = NULL;
    init_value_array(&chunk->constants);
}

void write_chunk(Chunk* chunk, Word op)
{
    if(chunk->len + 1 > chunk->capacity)
    {
        chunk->len = GROW_SIZE(chunk->len);
        chunk->codes = ALLOCATE(Word, &chunk->codes, chunk->len);
        chunk->lines = ALLOCATE(int, &chunk->lines, chunk->len);
    }
    chunk->codes[chunk->len++] = op;
}

int add_constant(Chunk* chunk, Value value)
{
    add_value(&chunk->constants, value);
    return chunk->constants.len - 1;
}

void free_chunk(Chunk* chunk)
{
    FREE(chunk->codes);
    FREE(chunk->lines);
    free_value_arr(&chunk->constants);
}

