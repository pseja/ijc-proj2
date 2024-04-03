#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

char *duplicate_string(const char *key)
{
    char *str = malloc(strlen(key) + 1);
    if (str == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for duplicate string\n");
        return NULL;
    }
    strcpy(str, key);
    return str;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    // use htab_find function to check if the key already exists
    htab_pair_t *existing_pair = htab_find(t, key);
    if (existing_pair != NULL)
    {
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
    new_item->pair->value = 0;
    new_item->pair->key = duplicate_string(key);
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
