#include "uart.h"

static uint32_t *const GPFSEL1 = (uint32_t *)         0x20200004;
static uint32_t *const AUX_ENABLES = (uint32_t *)     0x20215004;
static uint32_t *const AUX_MU_IO_REG = (uint32_t *)   0x20215040;
static uint32_t *const AUX_MU_IIR_REG = (uint32_t *)  0x20215048;
static uint32_t *const AUX_MU_LCR_REG = (uint32_t *)  0x2021504C;
static uint32_t *const AUX_MU_BAUD_REG = (uint32_t *) 0x20215068;
static uint32_t *const AUX_MU_LSR_REG = (uint32_t *)  0x20215054;

void print_byte(uint8_t byte) {
    // Wait until transmit FIFO is idle and empty
    while (((*AUX_MU_LSR_REG) & 0x60) != 0x60)
        ;
    *AUX_MU_IO_REG = byte;
}

void print(uint8_t *bytes) {
    while (*bytes) {
        print_byte(*bytes);
        ++bytes;
    }
}

uint8_t read_byte() {
    // Wait until receive FIFO is not empty
    while (!(*AUX_MU_LSR_REG & 1)) {
        if (*AUX_MU_LSR_REG & 1) {
            break;
        }
    }
    return *AUX_MU_IO_REG & 0xff;
}

void setup_uart() {
    // setup GPIO pins for UART
    uint32_t gpfsel1_value = *GPFSEL1;
    // transmit = gpio14
    gpfsel1_value &= ~(7<<12);
    gpfsel1_value |= 2<<12;
    // receive = gpio15
    gpfsel1_value &= ~(7<<15);
    gpfsel1_value |= 2<<15;
    *GPFSEL1 = gpfsel1_value;

    // setup UART
    *AUX_ENABLES = 1;
    *AUX_MU_LCR_REG = 3;
    *AUX_MU_IIR_REG = 0xC6;
    *AUX_MU_BAUD_REG = 270;
}
