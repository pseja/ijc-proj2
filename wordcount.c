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

    printf("🔥this is fine🔥\n");
    printf("htab_size: %zu\n", htab_size(hash_table));
    printf("htab_bucket_count: %zu\n", htab_bucket_count(hash_table));

    // read words from stdin

    htab_free(hash_table);

    return 0;
}
