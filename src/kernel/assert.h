#ifndef ASSERT_H_
#define ASSERT_H_

#include "stdio.h"

#define assert(expr) \
    printf("Assert failed with expression " #expr " in %s:%u, %s\r\n", \
        __FILE__, (unsigned long) __LINE__, __func__)

#endif // ASSERT_H_
