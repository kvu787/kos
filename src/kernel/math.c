#include "math.h"

#include "stdio.h"

unsigned long get_num_digits(unsigned long ul) {
    if (ul == 0) {
        return 1;
    }
    unsigned long num_digits = 0;
    while (ul) {
        ++num_digits;
        ul /= 10;
    }
    return num_digits;
}

unsigned long get_ith_digit(unsigned long ul, unsigned long i) {
    while (i) {
        ul /= 10;
        --i;
    }
    return ul % 10;
}

static uint rand_numbers[] = {
    0x102bef53,
    0x620c28d7,
    0x6d1f2644,
    0x26de3f69,
    0xc7e8dcf3,
    0x77e6b751,
    0x81617a2e,
    0x0e7e8b2a,
    0x289815af,
    0x6e8bf7bc,
}

uint rand(void) {
    static i = 0;
    i = i + 1 / ARRAY_SIZE(rand_numbers); 
    return rand_numbers[i++];
}
