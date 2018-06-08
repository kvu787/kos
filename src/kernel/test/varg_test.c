#include "varg_test.h"

#include "../stdio.h"
#include "../varg.h"

static unsigned char var1b = 0x1a;
static unsigned short var2b = 0xcafe;
static unsigned int var4b = 0xfaceface;

static bool varg_function(int a, char b, ...) {
    if (a != 0) {
        return false;
    }
    if (b != 1) {
        return false;
    }
    varg_data_t varg_data;
    varg_start(varg_data, b);
    if (varg_next(varg_data, int) != 2) {
        return false;
    }
    if (varg_next(varg_data, int) != 3) {
        return false;
    }
    if (varg_next(varg_data, unsigned char) != var1b) {
        return false;
    }
    if (varg_next(varg_data, int) != 4) {
        return false;
    }
    if (varg_next(varg_data, int) != 5) {
        return false;
    }
    if (varg_next(varg_data, unsigned short) != var2b) {
        return false;
    }
    if (varg_next(varg_data, int) != 6) {
        return false;
    }
    if (varg_next(varg_data, int) != 7) {
        return false;
    }
    if (varg_next(varg_data, unsigned int) != var4b) {
        return false;
    }
    if (varg_next(varg_data, int) != 8) {
        return false;
    }
    if (varg_next(varg_data, int) != 9) {
        return false;
    }
    return true;
}

bool varg_test(void) {
    return varg_function(0, 1, 2, 3, 
        var1b, 4, 5, var2b, 6, 7, var4b, 8, 9);
}
