#include "calc.h"

#include "char.h"
#include "io.h"
#include "math.h"
#include "types.h"
#include "vt100.h"

// Evaluates an reverse polish notation expression, such as "2 11 + 17 5 * *".
static uint_t rpn(char_t *expression);

#define COMMAND_LINE_SIZE 200

void calc_main(void) {
    while (TRUE) {
        while (TRUE) {
            puts("Press ENTER to continue or ESC to exit.");
            char_t c = getchar_silent();
            if (c == KEY_ENTER) {
                break;
            } else if (c == KEY_ESCAPE) {
                return;
            } else {
                continue;
            }
        }
        puts("Type a reverse polish notation expression and press ENTER to evaluate it.");
        char_t command_line[COMMAND_LINE_SIZE];
        if (getline(command_line, COMMAND_LINE_SIZE) == NULL) {
            printf("\r\nCommand too long. Max size is %u\r\n", COMMAND_LINE_SIZE-1);
            continue;
        }
        uint_t result = rpn(command_line);
        printf("%u\r\n", result);
    }
}

static uint_t rpn(char_t *expression) {
    static uint_t buffer[100];
    uint_t *stack = &buffer[0];

    // This loop does tokenization and evaluation in a single pass.
    // There's not really any parsing, because rpn is structured so that
    // the order of evaluation is already the left-to-right order of the
    // tokens. Normally, we'd parse to build the tree structure and
    // then traverse the tree to evaluate.
    //
    // Each iteration handles a token, which is one of:
    // spaces, operators, integers, \0
    while (TRUE) {
        char_t c = *expression;
        if (is_whitespace(c)) {
            while (is_whitespace(*expression)) {
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
        } else if (is_digit(c)) {
            uint_t n;
            sscanf(expression, "%u", &n);
            *stack++ = n;
            uint_t num_digits = get_num_digits(n);
            expression += num_digits;
        } else if (c == '\0') {
            break;
        }
    }

    return buffer[0];
}
