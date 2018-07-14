#include "cpu_test.h"

#include "../io.h"
#include "../time.h"

bool_t test_cpu() {
    // wait about 100 ms
    uint_t start_time = system_timer();
    spin(100);
    uint_t end_time = system_timer();
    // check elapsed time
    unsigned long microseconds_elapsed = end_time - start_time;
    if (!(90000 < microseconds_elapsed && microseconds_elapsed < 110000)) {
        printf("fail: microseconds_elapsed is %u, which is not within the expected range of 90000 to 110000");
        return FALSE;
    }
    return TRUE;
}
