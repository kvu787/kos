#ifndef STDIO_H_
#define STDIO_H_

#include <stddef.h>

// >= 0 on success
// = -1 on EOF
// < -1 on error
int getchar(void);

// >= 0 on success
// = -1 on EOF
// < -1 on error
int getchar_silent(void);

// >= 0 on success
// = -1 on EOF
// = -2 if no character available
// < -2 on error
int try_getchar_silent(void);

// NULL on error
char *gets(char *str, size_t n);

// Reads up to (size - 1) characters of user input until ENTER is sent.
// size = size of buffer
// Returns
//   buffer
//   Or NULL if user input exceeds buffer size.
char *getline(char *buffer, size_t size);

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

// Supports %d, %u, %s, %c, %%.
//
// >= 0 on success
// < 0 on error
int printf(const char *format, ...);

#endif // STDIO_H_
