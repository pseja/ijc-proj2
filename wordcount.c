#include <stdio.h>
#include <stdlib.h>
#include "htab.h"

#define DEBUG
#ifdef DEBUG
#include <assert.h> // TODO for testing only, delete after done testing
#endif

#define HASH_TABLE_SIZE 69 // temporary value

void print_htab_pair(htab_pair_t *pair)
{
    printf("%s: %d\n", pair->key, pair->value);
}

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

    printf("\n✏️ Adding text to hash table...\n");
    htab_pair_t *something1 = htab_lookup_add(hash_table, "something");
    printf("    > htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 1);

    printf("\n✏️ Adding another text to hash table...\n");
    htab_pair_t *else1 = htab_lookup_add(hash_table, "else");
    printf("    > htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 2);

    printf("\n✏️ Adding existing text to hash table...\n");
    htab_pair_t *something2 = htab_lookup_add(hash_table, "something");
    printf("    > htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 2);

    printf("\n✏️ Adding existing text to hash table...\n");
    htab_pair_t *something3 = htab_lookup_add(hash_table, "something1");
    printf("    > htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 3);

    printf("\n✏️ Adding existing text to hash table...\n");
    htab_pair_t *something4 = htab_lookup_add(hash_table, "something2");
    printf("    > htab_size: %zu\n", htab_size(hash_table));
    assert(htab_size(hash_table) == 4);

    printf("\n✏️ Trying to remove element from the hash table...\n");
    if (htab_erase(hash_table, "else"))
    {
        printf("    > Removed item from the hash table 😎\n");
        assert(htab_size(hash_table) == 3);
    }
    else
    {
        printf("    > Couldn't remove item due to it not existing or an error occured 😢\n");
        assert(htab_size(hash_table) == 4);
    }

    printf("\n✏️ Printing hash table...\n");
    htab_for_each(hash_table, print_htab_pair);
#endif

    // read words from stdin

    htab_free(hash_table);

    return 0;
}
