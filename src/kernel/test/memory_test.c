#include "memory_test.h"

#include "../assert.h"
#include "../memory.h"
#include "../string.h"
#include "../types.h"

static void memory_equals_test(void);
static void memory_set_test(void);
static void memory_copy_test(void);

void memory_test(void) {
    memory_equals_test();
    memory_set_test();
    memory_copy_test();
}

static void memory_equals_test(void) {
    byte_t buffer1[2] = {0xca, 0xfe};
    byte_t buffer2[2] = {0xfa, 0xce};
    assert(!memory_equals(&buffer1[0], &buffer2[0], 2));
    buffer2[0] = 0xca;
    buffer2[1] = 0xfe;
    assert(memory_equals(&buffer1[0], &buffer2[0], 2));
}

static void memory_set_test(void) {
    byte_t buffer[2] = {0xca, 0xfe};
    assert(buffer[0] == 0xca);
    assert(buffer[1] == 0xfe);
    memory_set(&buffer[0], 2, 1);
    assert(buffer[0] == 1);
    assert(buffer[1] == 1);
}

static void memory_copy_test(void) {
    byte_t src[] = {0xca, 0xfe};
    byte_t dst[20];
    memory_set(dst, 20, 0);
    memory_copy(src, dst, 2);
    assert(dst[0] == 0xca);
    assert(dst[1] == 0xfe);
}
