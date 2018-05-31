#include "keyecho.h"

#include <stdbool.h>

#include "stdio.h"
#include "vt100.h"

void keyecho_main(void) {
    puts("Press any key. The keycode(s) that it generates will be shown.");
    puts("Press ESC twice to exit.");
    bool wasLastCharacterEsc = false;
    while (true) {
        char c = getchar_silent();
        if (c == KEY_ESCAPE) {
            if (wasLastCharacterEsc) {
                return;
            } else {
                wasLastCharacterEsc = true;
            }
        } else {
            wasLastCharacterEsc = false;
        }
        printf("%u\r\n", c);
    }
}
