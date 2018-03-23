#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void print_byte(uint8_t byte);
void print(uint8_t *bytes);
uint8_t read_byte();
void setup_uart();

#endif // UART_H_
