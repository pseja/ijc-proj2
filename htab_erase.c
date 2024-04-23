// Lukáš Pšeja (xpsejal00)
// Fakulta informačních technologií Vysokého učení technického v Brně
// Příklad: 2
// 23.4.2024

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

bool htab_erase(htab_t *t, htab_key_t key)
{
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item *current_item = t->ptr_array[index];
    struct htab_item *previous_item = NULL;

    while (current_item != NULL)
    {
        if (strcmp(current_item->pair->key, key) == 0)
        {
            // if the item is the first one, set the pointer to the next item
            if (previous_item == NULL)
            {
                t->ptr_array[index] = current_item->next;
            }
            // if the item is not the first one, point the previous item to the next one
            else
            {
                previous_item->next = current_item->next;
            }

            free((void *)current_item->pair->key);
            free(current_item->pair);
            free(current_item);

            t->size--;

            // the pair got removed
            return true;
        }

        previous_item = current_item;
        current_item = current_item->next;
    }

    // the pair was not removed due to not existing
    return false;
}
