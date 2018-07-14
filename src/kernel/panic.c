#include "panic.h"

#include "io.h"
#include "types.h"

void panic(char *string) {
    printf(string);
    while (TRUE) {
    }
}

int panic_with_return(char *string) {
    panic(string);
    return 0;
}
