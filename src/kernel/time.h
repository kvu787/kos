#ifndef TIME_H_
#define TIME_H_

#include "types.h"

// Waste CPU cycles for the specified amount of time.
// This assumes we're running on a BCM2835,f since it assumes a particular
// clock speed.
void spin(uint_t milliseconds);


// Return the number of microseconds elapsed since power-on.
// Since it's 32 bits, it wraps around every ~72 minutes.
// Assumes we're running on a BCM2835.
uint_t system_timer();

#endif // TIME_H_
