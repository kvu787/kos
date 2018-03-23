#include "cpu.h"

void spin(uint32_t milliseconds) {
    milliseconds *= 4167;
    for (; milliseconds > 0; --milliseconds)
        ;
}
