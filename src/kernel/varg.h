#ifndef VARG_H_
#define VARG_H_

#include "types.h"

/*
When "..." is specified, the compiler pushes arguments from registers 
onto the a stack, creating a continuous stack of arguments. Earlier arguments
are stored at lower addresses. vargs walks this stack with the supplied type
information.

This example shows how arguments move from registers onto a stack: 

    Declaration: varg_function(int_t a, char_t *s, char_t c, ...)
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
#define __sizeof_align4(object) \
    ((sizeof(object) + 3) & ~3)

// varg_start must be called before calling varg_next.
// arg is the name of the argument before the ...
#define varg_init(arg) \
    ((unsigned) (((char_t *) &arg) + __sizeof_align4(arg)))

// varg_next accesses the next variadic argument.
// The type of the argument must be specified.
#define varg_next(varg_data, type) \
    (*((type *) __varg_next(&varg_data, __sizeof_align4(type), #type)))

void *__varg_next(varg_data_t *p_varg_data, int_t size, char_t *type_name);

#endif // VARG_H_
