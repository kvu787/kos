#include "panic.h"

#include "io.h"

void panic(char_t *string) {
    printf(string);
    while (TRUE) {
    }
}

int_t panic_with_return(char_t *string) {
    panic(string);
    return 0;
}
