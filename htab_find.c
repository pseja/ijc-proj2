#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key)
{
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *current_item = t->ptr_array[index];

    while (current_item != NULL)
    {
        if (strcmp(current_item->pair->key, key) == 0)
        {
            return current_item->pair;
        }
        current_item = current_item->next;
    }
    return NULL;
}
