#include "varg.h"

#include <string.h>

void *__varg_next(varg_data_t *p_varg_data, int type_size, char *type_name) {
    varg_data_t varg_data = *p_varg_data;
    // Handle types that are 8-byte aligned
    if ((strcmp(type_name, "unsigned long long") == 0)
        || (strcmp(type_name, "long long") == 0)
        || (strcmp(type_name, "double") == 0)
        || (strcmp(type_name, "float") == 0)) {
        if (varg_data % 8 != 0)  {
            varg_data += 4;
        }
    }
    void *return_value = (void *) varg_data;
    *p_varg_data = varg_data + type_size;
    return return_value;
}
