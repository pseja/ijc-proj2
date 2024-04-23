// Lukáš Pšeja (xpsejal00)
// Fakulta informačních technologií Vysokého učení technického v Brně
// Příklad: 2
// 23.4.2024

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    // use htab_find function to check if the key already exists
    htab_pair_t *existing_pair = htab_find(t, key);
    if (existing_pair != NULL)
    {
        existing_pair->value++;
        return existing_pair;
    }

    size_t input_index = htab_hash_function(key) % t->arr_size;

    // create a new item and initialize new item
    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL)
    {
        return NULL;
    }
    new_item->pair = NULL;
    new_item->next = NULL;

    // create a new pair in the item
    new_item->pair = malloc(sizeof(htab_pair_t));
    if (new_item->pair == NULL)
    {
        free(new_item);

        return NULL;
    }

    // insert data into the pair
    new_item->pair->value = 1;
    new_item->pair->key = strdup(key);
    if (new_item->pair->key == NULL)
    {
        free(new_item->pair);
        free(new_item);

        return NULL;
    }

    // and insert the pair at the start of the linked list
    new_item->next = t->ptr_array[input_index];
    t->ptr_array[input_index] = new_item;

    t->size++;

    return new_item->pair;
}
