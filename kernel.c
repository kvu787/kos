#include <stdint.h>

#include "cpu.h"
#include "uart.h"

void kernel_main() {
    setup_uart();

    // wait 10 seconds for client to connect TTY
    spin(10 * 1000);

    print("Testing print_byte... ");
    print_byte('p');
    print_byte('a');
    print_byte('s');
    print_byte('s');
    print_byte('\r');
    print_byte('\n');
    print("Testing print... ");
    print("pass\r\n");
    print("Testing read_byte... press any key to continue");
    read_byte();
    print("\r");
    print("Testing read_byte... pass                     \r\n");
    print("\r\n");

    print("Hello, welcome to kos.\r\n");
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
