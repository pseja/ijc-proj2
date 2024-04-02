#include "htab.h"

struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **ptr_array;
};
