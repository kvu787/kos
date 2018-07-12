#include "char_test.h"

#include "../assert.h"
#include "../char.h"

void char_test(void) {
    assert(is_whitespace(' '));
    assert(is_whitespace('\t'));
    assert(!is_whitespace('!'));

    assert(is_digit('0'));
    assert(is_digit('1'));
    assert(is_digit('2'));
    assert(is_digit('3'));
    assert(is_digit('4'));
    assert(is_digit('5'));
    assert(is_digit('6'));
    assert(is_digit('7'));
    assert(is_digit('8'));
    assert(is_digit('9'));
    assert(!is_digit('!'));

    assert(is_printable('~'));
    assert(!is_printable('\b'));
}
