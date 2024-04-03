#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(const size_t n)
{
    htab_t *hash_table = malloc(sizeof(htab_t));
    if (hash_table == NULL)
    {
        return NULL;
    }

    hash_table->size = 0;
    hash_table->arr_size = n;
    hash_table->ptr_array = calloc(hash_table->arr_size, sizeof(struct htab_item *));
    if (hash_table->ptr_array == NULL)
    {
        free(hash_table);
        return NULL;
    }

    return hash_table;
}
