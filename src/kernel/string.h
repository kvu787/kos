#ifndef STRING_H_
#define STRING_H_

#include "kos.h"

uint_t string_size(string_t string);
bool_t string_equals(string_t a, string_t b);
bool_t string_starts_with(string_t string, string_t prefix);

#endif // STRING_H_
