#ifndef VT100_H_
#define VT100_H_

// This defines the mapping of keycodes to keys and control sequences to their
// effects. Most are part of the ANSI terminal standard. They work with Tera
// Term, and probably many other terminal emulators too.

#define KEY_ESCAPE 27
#define KEY_ENTER 13

#define KEY_w 119
#define KEY_a 97
#define KEY_s 115
#define KEY_d 100

#define CTRL_CLEAR_SCREEN "\x1b[2J"
#define CTRL_MOVE_CURSOR_TOP_LEFT "\x1b[H"

// https://stackoverflow.com/a/9604357
#define CTRL_HIDE_CURSOR "\x1b[?25l"
#define CTRL_SHOW_CURSOR "\x1b[?25h"

#endif // VT100_H_
