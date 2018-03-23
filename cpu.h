#ifndef CPU_H_
#define CPU_H_

#include <stdint.h>

// Waste CPU cycles for the specified amount of time.
// This assumes we're running on a BCM2835, since it assumes a particular
// clock speed.
void spin(uint32_t milliseconds);

#endif // CPU_H_
