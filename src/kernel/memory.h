#ifndef MEMORY_H_
#define MEMORY_H_

#include "types.h"

bool_t memory_equals(void *a, void *b, uint_t size);
void memory_set(void *start, uint_t size, byte_t value);

#endif // MEMORY_H_
