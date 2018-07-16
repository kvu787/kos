#ifndef STDIO_H_
#define STDIO_H_

#include "types.h"

// >= 0 on success
// = -1 on EOF
// < -1 on error
int_t getchar(void);

// >= 0 on success
// = -1 on EOF
// < -1 on error
int_t getchar_silent(void);

// NULL on error
char_t *gets(char_t *str, uint_t n);

// Reads up to (size - 1) characters of user input until ENTER is sent.
// size = size of buffer
// Returns
//   buffer
//   Or NULL if user input exceeds buffer size.
char_t *getline(char_t *buffer, uint_t size);

// >= 0 on success
// < 0 on error
int_t putchar(char_t ch);

// >= 0 on success
// < 0 on error
int_t puts(const char_t *str);

// >= 0 on success
// -1 if format does not match input
int_t scanf(const char_t *format, ...);

// >= 0 on success
// -1 if format does not match input
int_t sscanf(const char_t *str, const char_t *format, ...);

// >= 0 on success
// < 0 on error
int_t printf(const char_t *format, ...);

#endif // STDIO_H_
