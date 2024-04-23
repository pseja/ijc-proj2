// Lukáš Pšeja (xpsejal00)
// Fakulta informačních technologií Vysokého učení technického v Brně
// Příklad: 2
// 23.4.2024

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

void htab_free(htab_t *t)
{
    htab_clear(t);
    free(t->ptr_array);
    free(t);
}
