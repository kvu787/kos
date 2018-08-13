#include "keyecho.h"

#include "io.h"
#include "terminal.h"
#include "types.h"

void keyecho_main(void) {
    puts("Press any key. The keycode(s) that it generates will be shown.");
    puts("Press ESC twice to exit.");
    bool_t wasLastCharacterEsc = FALSE;
    while (TRUE) {
        char_t c = getchar_silent();
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
