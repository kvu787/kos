#include "math.h"
#include "uart.h"

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

// https://stackoverflow.com/a/11946674
uint_t random(void) {
    static bool_t is_seed_initialized = FALSE;
    static uint_t seed;
    if (!is_seed_initialized) {
        is_seed_initialized = TRUE;
        seed = entropy & 0x7fffffff;
    }
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return seed;
}
