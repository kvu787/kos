#include "math.h"

uint_t get_num_digits(uint_t ul) {
    if (ul == 0) {
        return 1;
    }
    uint_t num_digits = 0;
    while (ul) {
        ++num_digits;
        ul /= 10;
    }
    return num_digits;
}

uint_t get_ith_digit(uint_t ul, uint_t i) {
    while (i) {
        ul /= 10;
        --i;
    }
    return ul % 10;
}
