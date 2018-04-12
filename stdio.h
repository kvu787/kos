#ifndef STDIO_H_
#define STDIO_H_

#include <stddef.h>

// >= 0 on success
// = -1 on EOF
// < -1 on error
int getchar(void);

// NULL on error
char *gets(char *str, size_t n);

// >= 0 on success
// < 0 on error
int putchar(char ch);

// >= 0 on success
// < 0 on error
int puts(const char *str);

// >= 0 on success
// -1 if format does not match input
int scanf(const char *format, ...);

// >= 0 on success
// -1 if format does not match input
int sscanf(const char *str, const char *format, ...);

// >= 0 on success
// < 0 on error
int printf(const char *format, ...);

void setup_uart();

#endif // STDIO_H_
