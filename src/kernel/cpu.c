#include "cpu.h"

static uint32_t *const TIMER_LOW = (uint32_t *) 0x20003004;

void spin(uint32_t milliseconds) {
    milliseconds *= 4167;
    for (; milliseconds > 0; --milliseconds) {
    }
}

uint32_t system_timer() {
    return *TIMER_LOW;
}
