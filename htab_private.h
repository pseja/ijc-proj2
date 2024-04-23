// Lukáš Pšeja (xpsejal00)
// Fakulta informačních technologií Vysokého učení technického v Brně
// Příklad: 2
// 23.4.2024

#include "htab.h"

struct htab_item
{
    htab_pair_t *pair;      // (key, data) pair
    struct htab_item *next; // pointer to the next htab_item in the array
};

struct htab
{
    size_t size;                  // number of htab_items in the table
    size_t arr_size;              // number of pointers in the htab_item ptr_array
    struct htab_item **ptr_array; // flexible array member
};
