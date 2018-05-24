#ifndef MATH_H_
#define MATH_H_

// Computes the number of digits used to represent ul in base 10.
unsigned long get_num_digits(unsigned long ul);

// Computes the number of digits used to represent ul in base 10.
unsigned long get_ith_digit(unsigned long ul, unsigned long i);

// Evaluates an reverse polish notation expression, such as "2 11 + 17 5 * *".
unsigned long rpn(char *expression);

#endif // MATH_H_