// Lukáš Pšeja (xpsejal00)
// Fakulta informačních technologií Vysokého učení technického v Brně
// Příklad: 2
// 23.4.2024

#include "htab_private.h"

size_t htab_bucket_count(const htab_t *t)
{
    return t->arr_size;
}
