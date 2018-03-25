#include "uart_test.h"

#include "uart.h"

void test_uart() {
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
}
