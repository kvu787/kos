#ifndef CHAR_H_
#define CHAR_H_

#include "types.h"

// Returns true iff c is a space or tab.
bool_t is_whitespace(char_t c);

// Returns true iff c is a digit (0-9).
bool_t is_digit(char_t c);

// Returns true iff c can be displayed in a cell, which means c is any ASCII
// character from '!' to '~'.
bool_t is_printable(char_t c);

#endif // CHAR_H_
