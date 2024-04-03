#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

#include <stdio.h>

void htab_clear(htab_t *t)
{
    for (size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *current_item = t->ptr_array[i];

        while (current_item != NULL)
        {
            free((void *)current_item->pair->key);
            free(current_item->pair);
            current_item->pair = NULL;

            // creating temporary item to safely free current item
            struct htab_item *temporary_item = current_item;
            current_item = current_item->next;
            free(temporary_item);

            t->size--;
        }
        t->ptr_array[i] = NULL;
    }
}
