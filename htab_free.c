#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

void htab_free(htab_t *t)
{
    // TODO htab_clear
    free(t->ptr_array);
    free(t);
}
