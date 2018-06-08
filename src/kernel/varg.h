#ifndef VARG_H_
#define VARG_H_

#include "panic.h"

/*
When "..." is specified, the compiler pushes arguments from registers 
onto the a stack, creating a continuous stack of arguments. Earlier arguments
are stored at lower addresses. vargs walks this stack with the supplied type
information.

This example shows how arguments move from registers onto a stack: 

    Declaration: varg_function(int a, char *s, char c, ...)
    Call: varg_function(1, "hello", 'w', var0, var1, var2)
    Arguments in registers and stack:
        r0:    1
        r1:    &"hello"
        sp+0:  'w'   (pushed from r2)
        sp+4:  var0  (pushed from r3)
        sp+8:  var1
        sp+12: var2
        sp+16: end of varg stack
*/

// Opaque object used to implement varg macros.
typedef unsigned varg_data_t;

// Arguments are 4-byte aligned on the stack.
#define __size_on_stack(var) \
    ((sizeof(var) + 3) & ~3)

// varg_start must be called before calling varg_next.
// arg is the name of the argument before the ...
#define varg_start(varg_data, arg) \
    varg_data = (unsigned) (((char *) &arg) + __size_on_stack(arg))

// varg_next accesses the next variadic argument.
// The type of the argument must be specified.
//
// TODO: For some reason, 8 byte types such as "unsigned long long" are 8-byte
// aligned, which produces padding on the stack, while large structs are
// unaligned. So for now this only supports types up to 4 bytes in size.
#define varg_next(varg_data, type) \
    ( \
        (sizeof(type) > 4) ? panic_with_return( \
            "varg argument type must not exceed 4 bytes") : 0, \
        varg_data += __size_on_stack(type), \
        (type) *((type *) (varg_data - __size_on_stack(type))) \
    )

#endif // VARG_H_
