#include "htab.h"
#include "htab_private.h"
#include <stdio.h>

void htab_statistics(const htab_t *t)
{
    unsigned min = -1;
    unsigned max = 0;
    unsigned sum = 0;

    for (size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *current_item = t->ptr_array[i];
        unsigned count = 0;

        while (current_item != NULL)
        {
            count++;

            current_item = current_item->next;
        }

        if (count < min)
        {
            min = count;
        }
        else if (count > max)
        {
            max = count;
        }

        sum += count;
    }

    fprintf(stderr, "    > Min: %u\n    > Max: %u\n    > Average: %f\n", min, max, (double)sum / (double)t->arr_size);
}
