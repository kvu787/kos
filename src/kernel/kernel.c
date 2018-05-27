#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

#include "cpu.h"
#include "math.h"
#include "stdio.h"
#include "uart.h"

#include "test/cpu_test.h"
#include "test/stdio_test.h"

#define COMMAND_LINE_SIZE 200

static void hang(void) {
    while (true) {
    }
}

void kernel_main(void) {
    // Run unit tests
    if (!test_stdio()) {
        puts("test_stdio failed");
        hang();
    }
    if (!test_cpu()) {
        puts("test_cpu failed");
        hang();
    }

    // Start shell
    puts("Hello, welcome to kos.");
    puts("Type a reverse polish notation expression and press ENTER to evaluate it.");
    char command_line[COMMAND_LINE_SIZE];
    while (true) {
        printf("> ");
        if (getline(command_line, COMMAND_LINE_SIZE) == NULL) {
            printf("\r\nCommand too long. Max size is %u\r\n", COMMAND_LINE_SIZE-1);
            continue;
        }
        unsigned long result = rpn(command_line);
        printf("%u\r\n", result);
    }
}
