#include <stdint.h>

#include "uart.h"

static uint8_t *const KERNEL_START = (uint8_t *) 0x9000;

void main(void) {
    // configure UART
    setup_uart();

    // receive first 4 bytes, parse as little endian integer X
    uint32_t kernel_size = 0;
    uint8_t *kernel_size_pointer = (uint8_t *) (&kernel_size);
    for (int i = 0; i < 4; ++i) {
        uint8_t byte = uart_getchar();
        *kernel_size_pointer++ = byte;
    }

    // receive next X bytes, copy to 0x8200
    uint8_t *kernel_pointer = KERNEL_START;
    while (kernel_size > 0) {
        uint8_t byte = uart_getchar();
        *kernel_pointer++ = byte;
        --kernel_size;
    }

    // wait for signal from terminal
    uart_getchar();

    // jump to kernel
    asm("b 0x9000");
}
