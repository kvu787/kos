#ifndef UART_H_
#define UART_H_

// Blocks until a byte is received from the UART.
char uart_getchar(void);

// Transmit a byte through the UART.
void uart_putchar(char ch);

#endif // UART_H_
