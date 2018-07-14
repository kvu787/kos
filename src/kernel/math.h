#ifndef MATH_H_
#define MATH_H_

#include "types.h"

// Computes the number of digits used to represent ul in base 10.
uint_t get_num_digits(uint_t ul);

// Computes the number of digits used to represent ul in base 10.
uint_t get_ith_digit(uint_t ul, uint_t i);

uint_t random(void);

#endif // MATH_H_
