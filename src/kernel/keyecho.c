#include "keyecho.h"

#include "io.h"
#include "types.h"
#include "vt100.h"

void keyecho_main(void) {
    puts("Press any key. The keycode(s) that it generates will be shown.");
    puts("Press ESC twice to exit.");
    bool_t wasLastCharacterEsc = FALSE;
    while (TRUE) {
        char c = getchar_silent();
        if (c == KEY_ESCAPE) {
            if (wasLastCharacterEsc) {
                return;
            } else {
                wasLastCharacterEsc = TRUE;
            }
        } else {
            wasLastCharacterEsc = FALSE;
        }
        printf("%u\r\n", c);
    }
}
