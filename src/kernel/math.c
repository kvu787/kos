#include "math.h"

#include "io.h"

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
