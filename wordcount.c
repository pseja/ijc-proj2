#include <stdio.h>
#include <stdlib.h>
#include "htab.h"

#define HASH_TABLE_SIZE 69 // temporary value

int main()
{
    htab_t *hash_table = htab_init(HASH_TABLE_SIZE);
    if (hash_table == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the hash table\n");
        return 1;
    }

    // read words from stdin

    // htab_free

    return 0;
}
