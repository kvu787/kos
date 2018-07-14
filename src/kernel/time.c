#include "time.h"

static uint_t *const TIMER_LOW = (uint_t *) 0x20003004;

void spin(uint_t milliseconds) {
    milliseconds *= 4167;
    for (; milliseconds > 0; --milliseconds) {
    }
}

uint_t system_timer() {
    return *TIMER_LOW;
}
