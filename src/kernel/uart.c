#include "uart.h"

#include <stdint.h>

static uint32_t *const GPFSEL1 = (uint32_t *)         0x20200004;
static uint32_t *const AUX_ENABLES = (uint32_t *)     0x20215004;
static uint32_t *const AUX_MU_IO_REG = (uint32_t *)   0x20215040;
static uint32_t *const AUX_MU_IIR_REG = (uint32_t *)  0x20215048;
static uint32_t *const AUX_MU_LCR_REG = (uint32_t *)  0x2021504C;
static uint32_t *const AUX_MU_BAUD_REG = (uint32_t *) 0x20215068;
static uint32_t *const AUX_MU_LSR_REG = (uint32_t *)  0x20215054;

// This is basically a UART driver.
// The most helpful resources I found while implementing this were
//   * Stanford's cs140e class: https://web.stanford.edu/class/cs140e/assignments/1-shell/
//   * dwelch67's working bare metal programs: https://github.com/dwelch67/raspberrypi
//     * The uart01/ folder in particular.
//   * The BCM2835 manual. Try to get the BCM2837 manual with errata fixes:
//     https://raspberrypi.stackexchange.com/a/78792/80441
void setup_uart(void) {
    /*** Setup GPIO pins for UART ***/

    // Read GPIO function select
    uint32_t gpfsel1_value = *GPFSEL1;

    // transmit = gpio14
    gpfsel1_value &= ~(7<<12);
    gpfsel1_value |= 2<<12;

    // receive = gpio15
    gpfsel1_value &= ~(7<<15);
    gpfsel1_value |= 2<<15;

    // Write GPIO function select
    *GPFSEL1 = gpfsel1_value;

    // BCM docs say that the UART will start receiving 0x0 characters if
    // the GPIO is not set up before-hand. GPIO 14 and 15 are pull-down by
    // default, so it seems like we should set them to pull-up before enabling
    // the UART? However, the tests clearly show that we're not getting a bunch
    // of 0x0 characters. So I assume that setting UART alt functions also
    // sets them to pull-up.

    /*** Setup UART ***/

    // Need to set this so we can toggle the following UART registers.
    *AUX_ENABLES = 1;

    // Use 8-bit mode, instead of 7-bit mode.
    // I think 7-bit mode uses the 8th bit for a parity check.
    *AUX_MU_LCR_REG = 3;

    // Clear transmit and receive FIFOs
    *AUX_MU_IIR_REG = 0xC6;

    // Apparently the BCM2835 system clock runs at 250 MHz.
    // See https://elinux.org/BCM2835_datasheet_errata#the_BCM2835_on_the_RPI

    // This register controls the baud rate.
    // The baud rate is a term for the bits per second transferred to and from the
    // UART devices. The devices must agree on the same baud rate, or else they
    // can't interpret the high and low signals properly.
    // 
    // System clock frequency = 250 MHz
    // Baudrate = 115200
    // baudrate_register = (250000000 / (8 * 115200)) - 1 = 270.27 ~= 270
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
