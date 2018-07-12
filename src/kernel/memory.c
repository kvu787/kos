#include "memory.h"

bool_t memory_equals(void *a, void *b, uint_t size) {
    byte_t *ab = (byte_t *) a;
    byte_t *bb = (byte_t *) b;
    for (uint_t i = 0; i < size; ++i) {
        if (ab[i] != bb[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

void memory_set(void *start, uint_t size, byte_t value) {
    byte_t *startb = (byte_t *) start;
    while (size > 0) {
        *startb++ = value;
        --size;
    }
}
