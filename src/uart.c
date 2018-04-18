#include "uart.h"

#include <stdint.h>

static uint32_t *const GPFSEL1 = (uint32_t *)         0x20200004;
static uint32_t *const AUX_ENABLES = (uint32_t *)     0x20215004;
static uint32_t *const AUX_MU_IO_REG = (uint32_t *)   0x20215040;
static uint32_t *const AUX_MU_IIR_REG = (uint32_t *)  0x20215048;
static uint32_t *const AUX_MU_LCR_REG = (uint32_t *)  0x2021504C;
static uint32_t *const AUX_MU_BAUD_REG = (uint32_t *) 0x20215068;
static uint32_t *const AUX_MU_LSR_REG = (uint32_t *)  0x20215054;

void setup_uart(void) {
    // setup GPIO pins for UART
    uint32_t gpfsel1_value = *GPFSEL1;
    // transmit = gpio14
    gpfsel1_value &= ~(7<<12);
    gpfsel1_value |= 2<<12;
    // receive = gpio15
    gpfsel1_value &= ~(7<<15);
    gpfsel1_value |= 2<<15;
    *GPFSEL1 = gpfsel1_value;

    // BCM docs say that the UART will start receiving 0x0 characters if
    // the GPIO is not set up before-hand. GPIO 14 and 15 are pull-down by
    // default, so it seems like we should set them to pull-up before enabling
    // the UART? However, the tests clearly show that we're not getting a bunch
    // of 0x0 characters. So I assume that setting UART alt functions also
    // sets them to pull-up.

    // setup UART
    *AUX_ENABLES = 1;
    *AUX_MU_LCR_REG = 3;
    *AUX_MU_IIR_REG = 0xC6;
    *AUX_MU_BAUD_REG = 270;
}

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
