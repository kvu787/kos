#ifndef MEMORY_H_
#define MEMORY_H_

#include "types.h"

// Returns true iff size bytes starting at a and b are equal.
bool_t memory_equals(void *a, void *b, uint_t size);

// Set size bytes beginning at start to value.
void memory_set(void *start, uint_t size, byte_t value);

// Copy size bytes from src dst.
void memory_copy(void *src, void *dst, uint_t size);

#endif // MEMORY_H_
