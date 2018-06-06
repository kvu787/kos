#include "uart.h"

#include <stdint.h>

static uint32_t *const AUX_MU_IO_REG = (uint32_t *)   0x20215040;
static uint32_t *const AUX_MU_LSR_REG = (uint32_t *)  0x20215054;

char uart_getchar(void) {
    // Wait until receive FIFO is not empty
    while (!(*AUX_MU_LSR_REG & 1)) {
    }
    return *AUX_MU_IO_REG & 0xff;
}

int uart_try_getchar(void) {
    if (*AUX_MU_LSR_REG & 1) {
        return *AUX_MU_IO_REG & 0xff;
    } else {
        return -1;
    }
}

void uart_putchar(char ch) {
    // Wait until transmit FIFO is idle and empty
    while (((*AUX_MU_LSR_REG) & 0x60) != 0x60) {
    }
    *AUX_MU_IO_REG = ch;
}
