#include "memory_test.h"

#include "../assert.h"
#include "../kos.h"
#include "../memory.h"
#include "../string.h"

static void memory_equals_test(void);
static void memory_set_test(void);

void memory_test(void) {
    memory_equals_test();
    memory_set_test();
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
