#ifndef ASSERT_H_
#define ASSERT_H_

#include "io.h"
#include "types.h"

#define assert(expr) (__assert(expr, #expr, __FILE__, __LINE__, __func__))

void __assert(bool_t ok, string_t expr, string_t file, uint_t line,
    string_t func);

#endif // ASSERT_H_
