#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

#include "assert.h"
#include "calc.h"
#include "cpu.h"
#include "keyecho.h"
#include "kos.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "uart.h"

#include "test/cpu_test.h"
#include "test/stdio_test.h"
#include "test/string_test.h"
#include "test/varg_test.h"

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
    if (!varg_test()) {
        puts("varg_test failed");
        hang();
    }
    string_test();

    // Print startup greeting
    puts("Hello, welcome to kos.");

    // Start shell
    while (true) {
        printf("> ");
        char command_line[COMMAND_LINE_SIZE];
        if (getline(command_line, COMMAND_LINE_SIZE) == NULL) {
            printf("\r\nCommand too long. Max size is %u\r\n.", COMMAND_LINE_SIZE-1);
            continue;
        }
        if (string_equals("help", command_line)) {
            printf(
                "Commands:\r\n"
                "  calc\r\n"
                "  help\r\n"
                "  keyecho\r\n"
                "  test_stdio_interactive\r\n");
        } else if (string_equals("calc", command_line)) {
            calc_main();
        } else if (string_equals("keyecho", command_line)) {
            keyecho_main();
        } else if (string_equals("test_stdio_interactive", command_line)) {
            if (test_stdio_interactive()) {
                puts("test_stdio_interactive passed");
            } else {
                puts("test_stdio_interactive failed");
            }
        } else {
            puts("Unrecognized command.");
        }
    }

    assert(FALSE);
}
