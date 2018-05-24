#ifndef UART_H_
#define UART_H_

// Configure the UART.
// This must be run before uart_getchar and uart_putchar are used.
void setup_uart(void);

// Blocks until a byte is received from the UART.
char uart_getchar(void);

// Transmit a byte through the UART.
void uart_putchar(char ch);

#endif // UART_H_
