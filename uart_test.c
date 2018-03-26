#include "uart_test.h"

#include <stdbool.h>
#include <stdint.h>

#include "uart.h"

static bool bytes_equal(uint8_t *a, uint8_t *b, uint32_t length) {
    for (; length > 0; --length) {
        if (*a != *b) {
            return false;
        }
        ++a;
        ++b;
    }
    return true;
}

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
    print("Press any key to continue\r\n");
    read_byte();
    print("pass\r\n");

    print("* Test read_byte_and_echo\r\n");
    print("Press any key and you should see it echoed back to the console\r\n");
    read_byte_and_echo();
    print("\r\n");
    print("pass\r\n");

    print("* Test read_until_and_echo\r\n");
    print("Type hello! and press ENTER. You should see hello echoed back to the console.\r\n");
    uint8_t buffer[20];
    uint32_t num_bytes_read = read_until_and_echo(buffer, '!');
    if (num_bytes_read != 5) {
        print("Wrong number of characters entered.\r\n");
    }
    uint8_t *expected = "hello";
    if (!bytes_equal(buffer, expected, 5)) {
        print("Wrong characters entered.");
    }
    print("\r\n");
    print("pass\r\n");
}
