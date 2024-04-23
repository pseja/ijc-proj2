// Lukáš Pšeja (xpsejal00)
// Fakulta informačních technologií Vysokého učení technického v Brně
// Příklad: 2
// 23.4.2024

#include "htab_private.h"

size_t htab_size(const htab_t *t)
{
    return t->size;
}
