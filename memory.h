#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

#define ALLOCATE(type, ptr, count) \
  (type*)reallocate(ptr, sizeof(type) * count)

#define FREE(ptr) (reallocate(ptr, 0))
#define GROW_SIZE(size) (size < 8 ? 8 : size*2)

void* reallocate(void* ptr, size_t size);
#endif 
