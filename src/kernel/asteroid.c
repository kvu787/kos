#include "asteroid.h"

#include <stdbool.h>
#include <stdint.h>

#include "cpu.h"
#include "kosdef.h"
#include "stdio.h"
#include "vt100.h"

static char *SCREEN =
"*                                                                              *"
"                                                                                "
"                                  +----------+                                  "
"                                  | ASTEROID |                                  "
"                                  +----------+                                  "
"                                                                                "
"                   PILOT YOUR SHIP THROUGH THE ASTEROID FIELD                   "
"                                                                                "
"                                                                                "
"                                    CONTROLS                                    "
"                                                                                "
"                              ENTER - START GAME                                "
"                                ESC - QUIT GAME                                 "
"                                  W - MOVE UP                                   "
"                                  A - MOVE LEFT                                 "
"                                  S - MOVE DOWN                                 "
"                                  D - MOVE RIGHT                                "
"                                                                                "
"                                                                                "
"                                   GOOD LUCK!                                   "
"                                                                                "
"                                                                                "
"                                                                                "
"*                                                                              *"
;

/*

Played on a 80 * 24 terminal

--------------------------------------------------------------------------------

                        ___Asteroids __
                       /               \
              *       /                 *
                     /
                    *
                                                                        *



                                                        *

                        *



                                                                    *


          *                                 *
                                __ Player
                               /
                              A
--------------------------------------------------------------------------------
*/


// The origin (0, 0) is at the bottom left of the screen

// 60 FPS
// 1/60th sec * 1,000,000 sec / microsecond = 16667 microseconds / frame
#define FRAME_DURATION 100000

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define SCREEN_BUFFER_SIZE (SCREEN_HEIGHT * SCREEN_WIDTH)

void screen_display() {
    for (int i = 0; i < SCREEN_BUFFER_SIZE; ++i) {
        putchar(SCREEN[i]);
    }
}

void screen_clear() {
    char *c = SCREEN;
    while (*c) {
        *c = ' ';
        ++c;
    }
}

// x = 40
// y = 1
void screen_write(char c, uint x, uint y) {
    uint col = x - 1; // 39
    uint row = SCREEN_HEIGHT - y; // 23
    uint index = row * SCREEN_WIDTH + col; // 23 * 80 + 39 = 1879
    SCREEN[index] = c;
}

typedef struct cursor {
    unsigned x;
    unsigned y;
} cursor_t;

void asteroid_main(void) {
    // Display title screen
    screen_display();

    // Await ENTER or ESC
    while (true) {
        char keypress = getchar_silent();
        if (keypress == KEY_ENTER) {
            break;
        } else if (keypress == KEY_ESCAPE) {
            return;
        } else {
            continue;
        }
    }


    uivec_t player_position = {40, 1};

    while (true) {
        // Frame timing
        uint32_t frame_start_time = system_timer();



        screen_clear();
        screen_write('A', player_position.x, player_position.y);
        screen_display();

        uint32_t frame_end_time = frame_start_time + FRAME_DURATION;
        while (system_timer() < frame_end_time) {
        }
    }
}
