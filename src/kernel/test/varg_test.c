#include "varg_test.h"

#include "../varg.h"

static unsigned char var1b = 0x1a;
static unsigned short var2b = 0xcafe;
static unsigned int var4b = 0xfaceface;
static unsigned long long int8b = 0xfeedfeedfeedfeed;
static float float4b = 181.38192;
static double double8b = 2.1728;

#define _check(type, expected) \
    if (varg_next(varg_data, type) != expected) { return false; }

static bool numeric_4_byte_function(int a, char b, ...) {
    if (a != 0) {
        return false;
    }
    if (b != 1) {
        return false;
    }
    varg_data_t varg_data = varg_init(b);
    _check(int, 2);
    _check(int, 3);
    _check(unsigned, var1b);
    _check(int, 4);
    _check(int, 5);
    _check(unsigned, var2b);
    _check(int, 6);
    _check(int, 7);
    _check(unsigned, var4b);
    _check(int, 8);
    _check(int, 9);
    return true;
}

static bool numeric_4_byte_test(void) {
    return numeric_4_byte_function(
        0, 1, 2, 3, var1b, 4, 5, var2b, 6, 7, var4b, 8, 9);
}

static bool numeric_8_byte_function(int a, char b, ...) {
    if (a != 0) {
        return false;
    }
    if (b != 1) {
        return false;
    }
    varg_data_t varg_data = varg_init(b);

    // Check padded accesses
    _check(int, 2);
    _check(double, double8b);
    _check(int, 3);
    _check(double, float4b);
    _check(int, 4);
    _check(unsigned long long, int8b);
    
    // Check unpadded accesses
    _check(double, double8b);
    _check(double, float4b);
    _check(unsigned long long, int8b);

    return true;
}

static bool numeric_8_byte_test(void) {
    return numeric_8_byte_function(
        0, 1, 2, double8b, 3, float4b, 4, int8b,
        double8b, float4b, int8b);
}

bool varg_test(void) {
    return 
        numeric_4_byte_test()
        && numeric_8_byte_test();
}
