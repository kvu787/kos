#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

#include "cpu.h"
#include "stdio.h"
#include "test/stdio_test.h"
#include "uart.h"

#define COMMAND_LINE_SIZE 200

static unsigned long get_num_digits(unsigned long ul) {
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

// Evaluates an reverse polish notation expression, such as "2 11 + 17 5 * *"
static unsigned long rpn(char *expression) {
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

static void hang(void) {
    while (true) {
    }
}

static char *getline(char *buffer, size_t size) {
    --size;
    while (size > 0) {
        char c = getchar();
        if (c == '\r') {
            break;
        } else {
            *buffer++ = c;
        }
        --size;
    }
    *buffer = '\0';
    return buffer;
}

void kernel_main(void) {
    setup_uart();

    // wait 10 seconds for client to connect TTY
    spin(10 * 1000);

    if (!test_stdio()) {
        puts("test_stdio failed");
        hang();
    }

    puts("Hello, welcome to kos.");
    puts("Type a reverse polish notation expression and press ENTER to evaluate it.");
    char command_line[COMMAND_LINE_SIZE];
    while (true) {
        getline(command_line, COMMAND_LINE_SIZE);
        unsigned long result = rpn(command_line);
        printf("%u\r\n", result);
    }
}
