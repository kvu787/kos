#include <stdint.h>

uint32_t *const GPFSEL1 = (uint32_t *)         0x20200004;
uint32_t *const AUX_ENABLES = (uint32_t *)     0x20215004;
uint32_t *const AUX_MU_IO_REG = (uint32_t *)   0x20215040;
uint32_t *const AUX_MU_IIR_REG = (uint32_t *)  0x20215048;
uint32_t *const AUX_MU_LCR_REG = (uint32_t *)  0x2021504C;
uint32_t *const AUX_MU_BAUD_REG = (uint32_t *) 0x20215068;
uint32_t *const AUX_MU_LSR_REG = (uint32_t *)  0x20215054;

void print_char(uint8_t ascii_char) {
    // Wait until transmit FIFO is idle and empty
    while (((*AUX_MU_LSR_REG) & 0x60) != 0x60)
        ;
    *AUX_MU_IO_REG = ascii_char;
}

void print(char *string) {
    while (*string) {
        print_char(*string);
        ++string;
    }
}

uint8_t read_char() {
    // Wait until receive FIFO is not empty
    while (!(*AUX_MU_LSR_REG & 1)) {
        if (*AUX_MU_LSR_REG & 1) {
            break;
        }
    }
    return *AUX_MU_IO_REG & 0xff;
}

void delay(uint32_t milliseconds) {
    milliseconds *= 4167;
    for (; milliseconds > 0; --milliseconds)
        ;
}

void kernel_main() {
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

    // wait 10 seconds for client to connect TTY
    delay(10 * 1000);

    print("Hello, welcome to kos.\r\n");
    print("Type something and you should see it echoed back to the console.\r\n");
    while (1) {
        uint8_t c = read_char();
        if (c == '\r') {
            print("\r\n");
        } else {
            print_char(c);
        }
    }
}
