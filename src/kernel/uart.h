#ifndef UART_H_
#define UART_H_

// Blocks until a byte is received from the UART.
char uart_getchar(void);

// Returns a byte received from UART.
// Returns -1 if no bytes have been received from the UART.
int uart_try_getchar(void);

// Transmit a byte through the UART.
void uart_putchar(char ch);

#endif // UART_H_
