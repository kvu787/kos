#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "calc.h"
#include "cpu.h"
#include "keyecho.h"
#include "math.h"
#include "stdio.h"
#include "uart.h"

#include "test/cpu_test.h"
#include "test/stdio_test.h"
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
        if (strcmp("help", command_line) == 0) {
            printf(
                "Commands:\r\n"
                "  calc\r\n"
                "  help\r\n"
                "  keyecho\r\n");
        } else if (strcmp("calc", command_line) == 0) {
            calc_main();
        } else if (strcmp("keyecho", command_line) == 0) {
            keyecho_main();
        } else {
            puts("Unrecognized command.");
        }
    }
}
