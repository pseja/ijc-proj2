#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data))
{
    for (size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *current_item = t->ptr_array[i];

        while (current_item != NULL)
        {
            htab_pair_t new_pair = {current_item->pair->key, current_item->pair->value};

            f(&new_pair);

            current_item = current_item->next;
        }
    }
}
