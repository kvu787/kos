#include "math.h"

#include <ctype.h>
#include <stdbool.h>

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


unsigned long rpn(char *expression) {
    static unsigned long buffer[100];
    unsigned long *stack = &buffer[0];

    // This loop does tokenization and evaluation in a single pass.
    // There's not really any parsing, because rpn is structured so that
    // the order of evaluation is already the left-to-right order of the
    // tokens. Normally, we'd parse to build the tree structure and
    // then traverse the tree to evaluate.
    // 
    // Each iteration handles a token, which is one of:
    // spaces, operators, integers, \0
    while (true) {
        char c = *expression;
        if (isspace(c)) {
            while (isspace(*expression)) {
                ++expression;
            }
        } else if (c == '+' || c == '*') {
            stack -= 2;
            if (c == '+') {
                *stack = stack[0] + stack[1];
            } else if (c == '*') {
                *stack = stack[0] * stack[1];
            }
            ++stack;
            ++expression;
        } else if (isdigit(c)) {
            unsigned long n;
            sscanf(expression, "%u", &n);
            *stack++ = n;
            unsigned long num_digits = get_num_digits(n);
            expression += num_digits;
        } else if (c == '\0') {
            break;
        }
    }

    return buffer[0];
}
