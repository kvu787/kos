#include <stdbool.h>

#include "cpu.h"
#include "stdio.h"

void kernel_main() {
    setup_uart();

    // wait 10 seconds for client to connect TTY
    spin(10 * 1000);

    puts("Hello, welcome to kos.");
    puts("Type something and you should see it echoed back to the console.");

    while (true) {
        getchar();
    }
}
