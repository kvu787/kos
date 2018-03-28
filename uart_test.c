#include "uart_test.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"

void test_uart() {
    print("* Test print_byte\r\n");
    print_byte('p');
    print_byte('a');
    print_byte('s');
    print_byte('s');
    print_byte('\r');
    print_byte('\n');

    print("* Test print\r\n");
    print("pass\r\n");

    print("* Test read_byte\r\n");
    print("Press any key to continue.\r\n");
    read_byte();
    print("pass\r\n");

    print("* Test read_byte_and_echo\r\n");
    print("Press any key and you should see it echoed back to the console.\r\n");
    read_byte_and_echo();
    print("\r\n");
    print("pass\r\n");

    print("* Test read_until_and_echo\r\n");
    print("Type hello! and you should see hello echoed back to the console.\r\n");
    uint8_t buffer[20];
    uint32_t num_bytes_read = read_until_and_echo(buffer, '!');
    if (num_bytes_read != 5) {
        print("Wrong number of characters entered.\r\n");
    }
    uint8_t *expected = "hello";
    if (memcmp(buffer, expected, 5) != 0) {
        print("Wrong characters entered.");
    }
    print("\r\n");
    print("pass\r\n");
}
