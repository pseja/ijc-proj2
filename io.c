#include "io.h"
#include <stdbool.h>

int read_word(char *s, int max, FILE *f)
{
    int ch = -1;
    int i = 0;
    static bool printed_warning = false; // program při prvním delším slovu vytiskne varování na stderr (max 1 varování)

    while ((ch = fgetc(f)) != EOF)
    {
        if (isspace(ch) && i == 0)
        {
            continue;
        }
        else if (isspace(ch))
        {
            break;
        }

        if (i < max - 1)
        {
            s[i] = ch;
        }
        else
        {
            if (!printed_warning)
            {
                fprintf(stderr, "Warning: The word you are trying to read is too long. Max: %d\n", max);
                printed_warning = true;
            }

            // read word until a space is reached or EOF
            while ((ch = fgetc(f)) != EOF && !isspace(ch))
            {
                continue;
            }
            break;
        }

        i++;
    }

    s[i] = '\0';

    // return i if the word ended correctly or EOF if the word ended with EOF
    if (i > 0 || ch != EOF)
    {
        return i;
    }
    else
    {
        return EOF;
    }
}
