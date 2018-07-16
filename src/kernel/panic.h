#ifndef PANIC_H_
#define PANIC_H_

#include "types.h"

// Print string and hang.
void panic(char_t *string);

// Hack to implement varg.h.
int_t panic_with_return(char_t *string);

#endif // PANIC_H_
