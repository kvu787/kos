#include "uart.h"

#include "io.h"
#include "time.h"
#include "types.h"

static uint_t *const AUX_MU_IO_REG = (uint_t *)  0x20215040;
static uint_t *const AUX_MU_LSR_REG = (uint_t *) 0x20215054;

uint_t entropy = 0;

char_t uart_getchar(void) {
    static uint_t prev_time = 0;

    // Set entropy
    if (prev_time == 0) {
        prev_time = system_timer();
    } else {
        entropy <<= 8;
        uint_t current_time = system_timer();
        uint_t diff = current_time - prev_time;
        entropy |= (diff & 0xff);
        prev_time = current_time;
    }

    // Wait until receive FIFO is not empty
    while (!(*AUX_MU_LSR_REG & 1)) {
    }
    return *AUX_MU_IO_REG & 0xff;
}

void uart_putchar(char_t ch) {
    // Wait until transmit FIFO is idle and empty
    while (((*AUX_MU_LSR_REG) & 0x60) != 0x60) {
    }
    *AUX_MU_IO_REG = ch;
}
