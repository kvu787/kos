#include "stdio.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

static uint32_t *const GPFSEL1 = (uint32_t *)         0x20200004;
static uint32_t *const AUX_ENABLES = (uint32_t *)     0x20215004;
static uint32_t *const AUX_MU_IO_REG = (uint32_t *)   0x20215040;
static uint32_t *const AUX_MU_IIR_REG = (uint32_t *)  0x20215048;
static uint32_t *const AUX_MU_LCR_REG = (uint32_t *)  0x2021504C;
static uint32_t *const AUX_MU_BAUD_REG = (uint32_t *) 0x20215068;
static uint32_t *const AUX_MU_LSR_REG = (uint32_t *)  0x20215054;

int getchar(void) {
    // Wait until receive FIFO is not empty
    while (!(*AUX_MU_LSR_REG & 1))
        ;
    char c = *AUX_MU_IO_REG & 0xff;
    if (c == '\r') {
        putchar('\r');
        putchar('\n');
    } else {
        putchar(c);
    }
    return c;
}

char *gets(char *str, size_t n) {
    while (n > 0) {
        *str++ = getchar();
        --n;
    }
    *str = '\0';
    return str;
}

int putchar(char ch) {
    // Wait until transmit FIFO is idle and empty
    while (((*AUX_MU_LSR_REG) & 0x60) != 0x60)
        ;
    *AUX_MU_IO_REG = ch;
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
int scanf(const char *format, ...) {

    // invariants
    // 
    // format: advance as input is parsed
    // 
    // args: advance as input is parsed
    // 
    // c:
    // >= 0 if c contains the next character
    // < 0 if getchar must be used to get the next character
    //
    // return_value: set to -1 if there is an error
    va_list args;
    va_start(args, format);
    int c = -1;
    int return_value = 0;

    while (*format) {
        if (c < 0) {
            c = (char) getchar();
        }
        if (strncmp("%u", format, 2) == 0) {
            // get digits
            unsigned long u = 0;
            while ('0' <= c && c <= '9') {
                u *= 10;
                u += c - '0';
                c = (char) getchar();                   
            }
            unsigned long *out_u = va_arg(args, unsigned long *);
            *out_u = u;
            format += 2;
        } else if (strncmp("%s", format, 2) == 0) {
            char *string = va_arg(args, char *);
            // get all [^\s\x0]
            while (c != '\0' && !isspace(c)) {
                *string++ = c;
                c = (char) getchar();
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

    va_end(args);
    return return_value;
}

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

static unsigned long get_ith_digit(unsigned long ul, unsigned long i) {
    while (i) {
        ul /= 10;
        --i;
    }
    return ul % 10;
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    while (*format) {
        if (strncmp("%u", format, 2) == 0) {
            unsigned long ul = va_arg(args, unsigned long);
            for (unsigned long i = get_num_digits(ul); i > 0; --i) {
                unsigned long digit = get_ith_digit(ul, i - 1);
                char c = ((char) digit) + '0';
                putchar(c);
            }
            format += 2;
        } else if (strncmp("%s", format, 2) == 0) {
            char *string = va_arg(args, char *);
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
    va_end(args);
    return 0;
}

void setup_uart() {
    // setup GPIO pins for UART
    uint32_t gpfsel1_value = *GPFSEL1;
    // transmit = gpio14
    gpfsel1_value &= ~(7<<12);
    gpfsel1_value |= 2<<12;
    // receive = gpio15
    gpfsel1_value &= ~(7<<15);
    gpfsel1_value |= 2<<15;
    *GPFSEL1 = gpfsel1_value;

    // setup UART
    *AUX_ENABLES = 1;
    *AUX_MU_LCR_REG = 3;
    *AUX_MU_IIR_REG = 0xC6;
    *AUX_MU_BAUD_REG = 270;
}
