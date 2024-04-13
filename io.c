#include "io.h"

int read_word(char *s, int max, FILE *f)
{
    int ch = 0;
    int i = 0;

    while ((ch = fgetc(f)) != EOF && i < max - 1)
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
            fprintf(stderr, "Warning: The word you are trying to read is too long. Max: %d\n", max);

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
