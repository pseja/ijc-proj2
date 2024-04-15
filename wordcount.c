#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

#define MAX_WORD_LENGTH 255
// proč zrovna hodnota 1'300'021:
// našel jsem na internetu (https://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-8.html),
// že ideální velikost je počet klíčů * 1.3 a velikost by měla být nejbližší vyšší prvočíslo k výsledku násobení,
// program jsem testoval na příkazu ze zadání "seq 1000000 2000000|shuf",
// kde se nachází milion čísel * 1.3 a nejbližší prvočíslo je 1'300'021
#define HASH_TABLE_SIZE 1299989

// error codes
#define ERR_HASH_TABLE_INIT 1
#define ERR_HASH_TABLE_ADD 2

// function prototypes
int load_hash_table(htab_t *hash_table, FILE *file, int max_word_length);
void print_htab_pair(htab_pair_t *pair);

int load_hash_table(htab_t *hash_table, FILE *file, int max_word_length)
{
    char word[MAX_WORD_LENGTH + 1];

    while (read_word(word, MAX_WORD_LENGTH, stdin) != EOF)
    {
        htab_pair_t *pair = htab_lookup_add(hash_table, word);
        if (pair == NULL)
        {
            htab_clear(hash_table);
            htab_free(hash_table);
            return ERR_HASH_TABLE_ADD;
        }
    }

    return 0;
}

void print_htab_pair(htab_pair_t *pair)
{
    printf("%s\t%d\n", pair->key, pair->value);
}

int main()
{
    htab_t *hash_table = htab_init(HASH_TABLE_SIZE);
    if (hash_table == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the hash table\n");
        return ERR_HASH_TABLE_INIT;
    }

    if (load_hash_table(hash_table, stdin, MAX_WORD_LENGTH))
    {
        fprintf(stderr, "Failed to add item to the hash table\n");
        return ERR_HASH_TABLE_ADD;
    }

    htab_for_each(hash_table, print_htab_pair);

#ifdef STATISTICS
    htab_statistics(hash_table);
#endif // STATISTICS

    htab_free(hash_table);

    return 0;
}
