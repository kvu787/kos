#include "char.h"

bool_t is_whitespace(char_t c) {
    return (c == ' ') || (c == '\t');
}

bool_t is_digit(char_t c) {
    return ('0' <= c) && (c <= '9');
}

bool_t is_printable(char_t c) {
    return ('!' <= c) && (c <= '~');
}
