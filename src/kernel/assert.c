#include "assert.h"

void __assert(bool_t ok, string_t expr, string_t file, uint_t line,
    string_t func) {
    if (!ok) {
        printf(
            "Assert failed with expression \"%s\" in %s:%u, %s\r\n",
            expr, file, line, func);
        while (TRUE) {
        }
    }
}
