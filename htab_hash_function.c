// Lukáš Pšeja (xpsejal00)
// Fakulta informačních technologií Vysokého učení technického v Brně
// Příklad: 2
// 23.4.2024

#include <stdint.h>
#include "htab_private.h"

// sdbm hash function from: http://www.cse.yorku.ca/~oz/hash.html
size_t htab_hash_function(const char *str)
{
    uint32_t h = 0; // musí mít 32 bitů

    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}
