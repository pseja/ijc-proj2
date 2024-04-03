#include <stdio.h>
#include <stdlib.h>
#include "htab.h"

#define DEBUG
#ifdef DEBUG
#include <assert.h> // TODO for testing only, delete after done testing
#endif

#define HASH_TABLE_SIZE 69 // temporary value

int main()
{
    htab_t *hash_table = htab_init(HASH_TABLE_SIZE);
    if (hash_table == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the hash table\n");
        return 1;
    }

#ifdef DEBUG
    printf("🔥this is fine🔥\n");
    printf("htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 0);
    printf("htab_bucket_count: %zu\n", htab_bucket_count(hash_table));
    assert(htab_bucket_count(hash_table) == HASH_TABLE_SIZE);

    printf("\nAdding text to hash table...\n");
    htab_pair_t *something1 = htab_lookup_add(hash_table, "something");
    printf("htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 1);

    printf("Adding another text to hash table...\n");
    htab_pair_t *else1 = htab_lookup_add(hash_table, "else");
    printf("htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 2);

    printf("Adding existing text to hash table...\n");
    htab_pair_t *something2 = htab_lookup_add(hash_table, "something");
    printf("htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 2);
#endif

    // read words from stdin

    htab_free(hash_table);

    return 0;
}
