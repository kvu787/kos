#include "io.h"

#include "char.h"
#include "math.h"
#include "string.h"
#include "types.h"
#include "uart.h"
#include "varg.h"

static const int_t DOUBLE_PRECISION = 2;

int_t getchar(void) {
    char_t c = getchar_silent();
    if (c == '\r') {
        putchar('\r');
        putchar('\n');
    } else {
        putchar(c);
    }
    return c;
}

int_t getchar_silent(void) {
    return uart_getchar();
}

char_t *gets(char_t *str, uint_t n) {
    while (n > 0) {
        *str++ = getchar();
        --n;
    }
    *str = '\0';
    return str;
}

char_t *getline(char_t *buffer, uint_t size) {
    --size;
    bool_t hasReceivedEnter = FALSE;
    while (size > 0 && !hasReceivedEnter) {
        char_t c = getchar();
        if (c == '\r') {
            hasReceivedEnter = TRUE;
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

int_t putchar(char_t ch) {
    uart_putchar(ch);
    return 0;
}

int_t puts(const char_t *str) {
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
static int_t vscanf(int_t (*getchar_f)(void), const char_t *format, varg_data_t args) {
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
    int_t c = -1;
    int_t return_value = 0;

    while (*format) {
        if (c < 0) {
            c = (char_t) getchar_f();
        }
        if (string_starts_with(format, "%u")) {
            // get digits
            uint_t u = 0;
            while (is_digit(c)) {
                u *= 10;
                u += c - '0';
                c = (char_t) getchar_f();
            }
            uint_t *out_u = varg_next(args, uint_t *);
            *out_u = u;
            format += 2;
        } else if (string_starts_with(format, "%s")) {
            char_t *string = varg_next(args, char_t *);
            // get all [^\s\x0]
            while (is_printable(c)) {
                *string++ = c;
                c = (char_t) getchar_f();
            }
            *string = '\0';
            format += 2;
        } else if (string_starts_with(format, "%%")) {
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

int_t scanf(const char_t *format, ...) {
    int_t (*getchar_f)(void) = &getchar;
    varg_data_t args = varg_init(format);
    int_t return_value = vscanf(getchar_f, format, args);
    return return_value;
}

static const char_t *sgetchar_string;

static int_t sgetchar(void) {
    if (sgetchar_string) {
        return *sgetchar_string++;
    } else {
        return -1;
    }
}

// Returns a getchar_t function for the given string.
// The string is stored in a global variable, because C doesn't closures which
// could capture state local to the function that isn't already passed in
// through arguments.
static int_t (*generate_sgetchar(const char_t *string))(void) {
    sgetchar_string = string;
    return &sgetchar;
}

int_t sscanf(const char_t *str, const char_t *format, ...) {
    int_t (*getchar_f)(void) = generate_sgetchar(str);
    varg_data_t args = varg_init(format);
    int_t return_value = vscanf(getchar_f, format, args);
    return return_value;
}

int_t printf(const char_t *format, ...) {
    varg_data_t args = varg_init(format);
    while (*format) {
        if (string_starts_with(format, "%d")) {
            double d = varg_next(args, double);
            // Handle negatives
            if (d < 0) {
                putchar('-');
                d = -d;
            }
            // Print whole part
            uint_t ul = (uint_t) d;
            printf("%u", ul);
            // Print fractional part
            putchar('.');
            double fractional = d;
            for (int_t i = 0; i < DOUBLE_PRECISION; ++i) {
                fractional = fractional - ((uint_t) fractional);
                fractional *= 10;
                printf("%u", (uint_t) fractional);
            }
            format += 2;
        } else if (string_starts_with(format, "%u")) {
            uint_t ul = varg_next(args, uint_t);
            for (uint_t i = get_num_digits(ul); i > 0; --i) {
                uint_t digit = get_ith_digit(ul, i - 1);
                char_t c = ((char_t) digit) + '0';
                putchar(c);
            }
            format += 2;
        } else if (string_starts_with(format, "%s")) {
            char_t *string = varg_next(args, char_t *);
            while (*string) {
                putchar(*string++);
            }
            format += 2;
        } else if (string_starts_with(format, "%%")) {
            putchar('%');
            format += 2;
        } else {
            putchar(*format);
            ++format;
        }
    }
    return 0;
}
