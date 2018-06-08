#ifndef PANIC_H_
#define PANIC_H_

// Print string and hang.
void panic(char *string);

// Hack to implement varg.h.
int panic_with_return(char *string);

#endif // PANIC_H_
