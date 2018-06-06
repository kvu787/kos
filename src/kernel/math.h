#ifndef MATH_H_
#define MATH_H_

#include "array.h"
#include "kosdef.h"

// Computes the number of digits used to represent ul in base 10.
unsigned long get_num_digits(unsigned long ul);

// Computes the number of digits used to represent ul in base 10.
unsigned long get_ith_digit(unsigned long ul, unsigned long i);

uint rand(void);

// // Returns the largest integer that is smaller or equal to f.
// int floor(float f);

#endif // MATH_H_
