#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(const size_t n)
{
    htab_t *table = malloc(sizeof(htab_t));
    if (table == NULL)
    {
        return NULL;
    }

    table->size = 0;
    table->arr_size = n;
    table->ptr_array = malloc(table->arr_size * sizeof(struct htab_item *));
    if (table->ptr_array == NULL)
    {
        free(table);
        return NULL;
    }

    return table;
}
