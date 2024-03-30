#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *file = NULL;
    int num_of_lines = 10;

    for (unsigned i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Invalid amount of arguments\n");
                return 1;
            }

            num_of_lines = atoi(argv[++i]);

            if (num_of_lines <= 0)
            {
                fprintf(stderr, "Invalid number of lines\n");
                return 1;
            }
        }
        else if (file == NULL)
        {
            file = fopen(argv[i], "r");

            if (file == NULL)
            {
                fprintf(stderr, "Couldn't open file %s\n", argv[i]);
                return 1;
            }
#ifdef DEBUG
            printf("file: %s\n", argv[i]);
#endif
        }
        else
        {
            fprintf(stderr, "Invalid amount of arguments\n");
            return 1;
        }
    }

    if (file == NULL)
    {
        file = stdin;
#ifdef DEBUG
        printf("file: stdin\n");
#endif
    }
#ifdef DEBUG
    printf("num_of_lines: %d\n", num_of_lines);
#endif

    if (fclose(file) != 0)
    {
        fprintf(stderr, "Couldn't close file\n");
        return 1;
    }

    return 0;
}