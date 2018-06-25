#include "string.h"

uint_t string_size(string_t string) {
    uint_t size = 0;
    while (*string++) {
        ++size;
    }
    return size;
}

bool_t string_equals(string_t a, string_t b) {
    uint_t size_a = string_size(a);
    if (size_a == string_size(b)) {
        for (uint_t i = 0; i < size_a; ++i) {
            if (a[i] != b[i]) {
                return FALSE;
            }
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

bool_t string_starts_with(string_t string, string_t prefix) {
    uint_t prefix_size = string_size(prefix);
    if (string_size(prefix) > string_size(string)) {
        return FALSE;
    }
    for (uint_t i = 0; i < prefix_size; ++i) {
        if (string[i] != prefix[i]) {
            return FALSE;
        }
    }
    return TRUE;
}
