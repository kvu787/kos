#include "varg.h"

#include "string.h"

void *__varg_next(varg_data_t *p_varg_data, int type_size, char *type_name) {
    varg_data_t varg_data = *p_varg_data;
    // Handle types that are 8-byte aligned
    if ((string_equals(type_name, "unsigned long long"))
        || (string_equals(type_name, "long long"))
        || (string_equals(type_name, "double"))
        || (string_equals(type_name, "float"))) {
        if (varg_data % 8 != 0)  {
            varg_data += 4;
        }
    }
    void *return_value = (void *) varg_data;
    *p_varg_data = varg_data + type_size;
    return return_value;
}
