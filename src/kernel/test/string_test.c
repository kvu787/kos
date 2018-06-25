#include "../assert.h"
#include "../string.h"

void string_test(void) {
    string_t a = "hello, world";
    string_t b = "hola, mundo";

    assert(string_size(a) == 12);
    assert(string_size(b) == 11);
    assert(string_size("") == 0);
    assert(!string_equals(a, b));
    b = "hello, world";
    assert(string_equals(a, b));
    assert(string_equals("", ""));
    assert(!string_equals(a, ""));
}
