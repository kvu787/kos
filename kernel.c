#include <stdint.h>

#include "cpu.h"
#include "uart.h"
#include "uart_test.h"

void kernel_main() {
    setup_uart();

    // wait 10 seconds for client to connect TTY
    spin(10 * 1000);

    test_uart();
    print("\r\n");

    print("Hello, welcome to kos.\r\n");
    print("Type help and press ENTER to view commands.");

    print("Type something and you should see it echoed back to the console.\r\n");
    while (1) {
        uint8_t c = read_byte();
        if (c == '\r') {
            print("\r\n");
        } else {
            print_byte(c);
        }
    }
}
