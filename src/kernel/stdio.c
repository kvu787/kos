#include "stdio.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "math.h"
#include "uart.h"
#include "varg.h"

static const int DOUBLE_PRECISION = 2;

int getchar(void) {
    char c = getchar_silent();
    if (c == '\r') {
        putchar('\r');
        putchar('\n');
    } else {
        putchar(c);
    }
    return c;
}

int getchar_silent(void) {
    return uart_getchar();
}

char *gets(char *str, size_t n) {
    while (n > 0) {
        *str++ = getchar();
        --n;
    }
    *str = '\0';
    return str;
}

char *getline(char *buffer, size_t size) {
    --size;
    bool hasReceivedEnter = false;
    while (size > 0 && !hasReceivedEnter) {
        char c = getchar();
        if (c == '\r') {
            hasReceivedEnter = true;
        } else {
            *buffer++ = c;
            --size;
        }
    }
    if (!hasReceivedEnter && getchar() != '\r') {
        return NULL;
    } else {
        *buffer = '\0';
        return buffer;
    }
}

int putchar(char ch) {
    uart_putchar(ch);
    return 0;
}

int puts(const char *str) {
    while (*str) {
        putchar(*str);
        ++str;
    }
    putchar('\r');
    putchar('\n');
    return 0;
}

// %s: [^\s\x0] followed by [\s\x0], but whitespace not included
// %d: [0-9] followed by [^0-9]
// %%: %
// Every other character: character
// 
// Precondition: the character stream is not shorter than format
// ^TODO: handle EOF properly
static int vscanf(int (*getchar_f)(void), const char *format, varg_data_t args) {
    // invariants
    // 
    // format: advance as input is parsed
    // 
    // args: advance as input is parsed
    // 
    // c:
    // >= 0 if c contains the next character
    // < 0 if getchar_f must be used to get the next character
    //
    // return_value: set to -1 if there is an error
    int c = -1;
    int return_value = 0;

    while (*format) {
        if (c < 0) {
            c = (char) getchar_f();
        }
        if (strncmp("%u", format, 2) == 0) {
            // get digits
            unsigned long u = 0;
            while ('0' <= c && c <= '9') {
                u *= 10;
                u += c - '0';
                c = (char) getchar_f();
            }
            unsigned long *out_u = varg_next(args, unsigned long *);
            *out_u = u;
            format += 2;
        } else if (strncmp("%s", format, 2) == 0) {
            char *string = varg_next(args, char *);
            // get all [^\s\x0]
            while (c != '\0' && !isspace(c)) {
                *string++ = c;
                c = (char) getchar_f();
            }
            *string = '\0';
            format += 2;
        } else if (strncmp("%%", format, 2) == 0) {
            if (c == '%') {
                format += 2;
                c = -1;
            } else {
                return_value = -1;
                break;
            }
        } else {
            if (*format == c) {
                ++format;
                c = -1;
            } else {
                return_value = -1;
                break;
            }
        }
    }

    return return_value;
}

int scanf(const char *format, ...) {
    int (*getchar_f)(void) = &getchar;
    varg_data_t args = varg_init(format);
    int return_value = vscanf(getchar_f, format, args);
    return return_value;
}

static const char *sgetchar_string;

static int sgetchar(void) {
    if (sgetchar_string) {
        return *sgetchar_string++;
    } else {
        return -1;
    }
}

// Returns a getchar function for the given string.
// The string is stored in a global variable, because C doesn't closures which
// could capture state local to the function that isn't already passed in
// through arguments.
static int (*generate_sgetchar(const char *string))(void) {
    sgetchar_string = string;
    return &sgetchar;
}

int sscanf(const char *str, const char *format, ...) {
    int (*getchar_f)(void) = generate_sgetchar(str);
    varg_data_t args = varg_init(format);
    int return_value = vscanf(getchar_f, format, args);
    return return_value;
}

int printf(const char *format, ...) {
    varg_data_t args = varg_init(format);
    while (*format) {
        if (strncmp("%d", format, 2) == 0) {
            double d = varg_next(args, double);
            // Handle negatives
            if (d < 0) {
                putchar('-');
                d = -d;
            }
            // Print whole part
            unsigned long ul = (unsigned long) d;
            printf("%u", ul);
            // Print fractional part
            putchar('.');
            double fractional = d;
            for (int i = 0; i < DOUBLE_PRECISION; ++i) {
                fractional = fractional - ((unsigned long) fractional);
                fractional *= 10;
                printf("%u", (unsigned long) fractional);
            }
            format += 2;
        } else if (strncmp("%u", format, 2) == 0) {
            unsigned long ul = varg_next(args, unsigned long);
            for (unsigned long i = get_num_digits(ul); i > 0; --i) {
                unsigned long digit = get_ith_digit(ul, i - 1);
                char c = ((char) digit) + '0';
                putchar(c);
            }
            format += 2;
        } else if (strncmp("%s", format, 2) == 0) {
            char *string = varg_next(args, char *);
            while (*string) {
                putchar(*string++);
            }
            format += 2;
        } else if (strncmp("%%", format, 2) == 0) {
            putchar('%');
            format += 2;
        } else {
            putchar(*format);
            ++format;
        }
    }
    return 0;
}
