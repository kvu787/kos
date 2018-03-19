#include <stdint.h>

uint32_t *const GPFSEL1 = (uint32_t *)         0x20200004;
uint32_t *const AUX_ENABLES = (uint32_t *)     0x20215004;
uint32_t *const AUX_MU_IO_REG = (uint32_t *)   0x20215040;
uint32_t *const AUX_MU_IIR_REG = (uint32_t *)  0x20215048;
uint32_t *const AUX_MU_LCR_REG = (uint32_t *)  0x2021504C;
uint32_t *const AUX_MU_BAUD_REG = (uint32_t *) 0x20215068;
uint32_t *const AUX_MU_LSR_REG = (uint32_t *)  0x20215054;

void print_char(uint8_t ascii_char) {
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

void delay(uint32_t milliseconds) {
    milliseconds *= 4167;
    for (; milliseconds > 0; --milliseconds)
        ;
}

void kernel_main() {
    uint32_t gpfsel1_value = *GPFSEL1;
    gpfsel1_value &= ~(7<<12);
    gpfsel1_value |= 2<<12;
    *GPFSEL1 = gpfsel1_value;

    *AUX_ENABLES = 1;
    *AUX_MU_LCR_REG = 3;
    *AUX_MU_IIR_REG = 0xC6;
    *AUX_MU_BAUD_REG = 270;

    delay(10 * 1000);

    print("hello, world\r\n");
    print("\r\n");
    print("Printing graphical ASCII characters forever... ");
    uint8_t ascii_char = 32;
    while (1) {
        print_char(ascii_char);
        ++ascii_char;
        if (ascii_char == 127) {
            ascii_char = 32;
        }
        delay(100);
    }
}
