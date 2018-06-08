#include "panic.h"

#include <stdbool.h>

#include "stdio.h"

void panic(char *string) {
    printf(string);
    while (true) {
    }
}

int panic_with_return(char *string) {
    panic(string);
    return 0;
}
