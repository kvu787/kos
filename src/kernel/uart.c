#include "uart.h"

#include "types.h"

static uint_t *const AUX_MU_IO_REG = (uint_t *)  0x20215040;
static uint_t *const AUX_MU_LSR_REG = (uint_t *) 0x20215054;

char uart_getchar(void) {
    // Wait until receive FIFO is not empty
    while (!(*AUX_MU_LSR_REG & 1)) {
    }
    return *AUX_MU_IO_REG & 0xff;
}

void uart_putchar(char ch) {
    // Wait until transmit FIFO is idle and empty
    while (((*AUX_MU_LSR_REG) & 0x60) != 0x60) {
    }
    *AUX_MU_IO_REG = ch;
}
