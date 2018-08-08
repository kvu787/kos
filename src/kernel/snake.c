#include "snake.h"

#include "io.h"
#include "math.h"
#include "string.h"
#include "time.h"
#include "types.h"
#include "vt100.h"

// 10 FPS
#define FRAME_DURATION_USECS 100000

#define SNAKE_INITIAL_LENGTH 3

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define SCREEN_SIZE (SCREEN_HEIGHT * SCREEN_WIDTH)

static char const *const TITLE_SCREEN = 
"*                                                                              *"
"                                                                                "
"                                  +---------+                                   "
"                                  |  SNAKE  |                                   "
"                                  +---------+                                   "
"                                                                                "
"                                                                                "
"                      GROW YOUR SNAKE BY EATING THE APPLES                      "
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
"*                                                                              *"
;

static char SCREEN[SCREEN_WIDTH * SCREEN_HEIGHT];

void screen_display(void) {
    // Clear terminal
    printf(CTRL_CLEAR_SCREEN);

    // Move cursor to upper left corner
    printf(CTRL_MOVE_CURSOR_TOP_LEFT);

    // Print screen buffer
    for (int i = 0; i < SCREEN_SIZE; ++i) {
        putchar(SCREEN[i]);
    }
}

void screen_clear(void) {
    for (uint_t i = 0; i < SCREEN_SIZE; ++i) {
        SCREEN[i] = ' ';
    }
}

void screen_write(char c, uint_t x, uint_t y) {
    uint_t col = x; // 39
    uint_t row = SCREEN_HEIGHT - y - 1;
    uint_t index = row * SCREEN_WIDTH + col;
    SCREEN[index] = c;
}

typedef struct {
    uint_t x;
    uint_t y;
} position_t;

void spawn_new_apple(position_t *apple) {
    *apple = (position_t){random() % SCREEN_WIDTH, random() % SCREEN_HEIGHT};
}

bool_t position_equals(position_t a, position_t b) {
    return (a.x == b.x) && (a.y == b.y);
}

// The head of the snake is at index 0.
static uint_t snake_length;
static position_t snake_positions[SCREEN_WIDTH * SCREEN_HEIGHT];

void snake_main(void) {
    // Hide cursor
    printf(CTRL_HIDE_CURSOR);

    // Display title screen
    for (uint_t i = 0; i < SCREEN_SIZE; ++i) {
        SCREEN[i] = TITLE_SCREEN[i];
    }
    screen_display();

    // Await ENTER or ESC
    while (TRUE) {
        char keypress = getchar_silent();
        if (keypress == KEY_ENTER) {
            break;
        } else if (keypress == KEY_ESCAPE) {
            return;
        } else {
            continue;
        }
    }

    ////// INITIAL GAME DATA //////

    // Snake
    snake_length = SNAKE_INITIAL_LENGTH;
    for (uint_t i = 0; i < snake_length; ++i) {
        snake_positions[i] = (position_t){10 - i, 12};
    }
    char_t input = KEY_d;
    bool_t is_snake_alive = TRUE;
    // Apple
    uint_t apples_eaten = 0;
    bool_t was_apple_eaten = FALSE;
    position_t apple_position;
    spawn_new_apple(&apple_position);
    // Frame time
    uint_t next_frame_start_time = 0;

    ////// GAME LOOP //////

    while (TRUE) {

        ////// WAIT FOR NEXT FRAME ///////

        while (system_timer() < next_frame_start_time) {
        }
        next_frame_start_time = system_timer() + FRAME_DURATION_USECS;

        /////// READ INPUT //////

        int_t i = try_getchar_silent();
        if (i >= 0) {
            char_t ch = (char_t) i;
            switch (ch) {
                case KEY_w:
                case KEY_a:
                case KEY_s:
                case KEY_d:
                    input = ch;
                    break;
            }
        }

        ////// UPDATE GAME STATE //////

        if (was_apple_eaten) {
            ++snake_length;
        }

        // Shift first LENGTH-1 sections to the right
        // This deletes the tail, makes room for the new head, and preserves the
        // positions of the body
        for (uint_t i = snake_length - 2; ; --i) {
            snake_positions[i + 1] = snake_positions[i];
            if (i == 0) {
                break;
            }
        }
        position_t *new_head = &snake_positions[0];
        switch (input) {
            case KEY_w:
                ++(new_head->y);
                break;
            case KEY_a:
                --(new_head->x);
                break;
            case KEY_s:
                --(new_head->y);
                break;
            case KEY_d:
                ++(new_head->x);
                break;
        }

        // Did snake eat itself?
        for (uint_t i = 1; i < snake_length; ++i) {
            if (position_equals(snake_positions[0], snake_positions[i])) {
                is_snake_alive = FALSE;
            }
        }

        // Did snake hit the wall?
        if ((new_head->x < 0)
            || (new_head->x >= SCREEN_WIDTH)
            || (new_head->y < 0)
            || (new_head->y >= SCREEN_HEIGHT)) {
            is_snake_alive = FALSE;
        }

        // Check for game over
        if (!is_snake_alive) {
            printf(CTRL_CLEAR_SCREEN);
            printf(CTRL_MOVE_CURSOR_TOP_LEFT);
            puts("GAME OVER!");
            printf("YOU ATE %u APPLES.\r\n", apples_eaten);
            puts("PRESS ENTER TO EXIT THE GAME.");
            while (TRUE) {
                if (getchar_silent() == KEY_ENTER) {
                    printf(CTRL_CLEAR_SCREEN);
                    printf(CTRL_MOVE_CURSOR_TOP_LEFT);
                    printf(CTRL_SHOW_CURSOR);
                    return;
                }
            }
        }

        // Check if snake ate the apple
        if (position_equals(snake_positions[0], apple_position)) {
            ++apples_eaten;
            // Spawn a new apple
            spawn_new_apple(&apple_position);
            was_apple_eaten = TRUE;
        } else {
            was_apple_eaten = FALSE;
        }

        ////// DISPLAY //////

        screen_clear();
        for (uint_t i = 0; i < snake_length; ++i) {
            screen_write('O', snake_positions[i].x, snake_positions[i].y);
        }
        screen_write('*', apple_position.x, apple_position.y);
        screen_display();
    }
}
