#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define DEBUG
#define MAX_LINE_LENGTH 2047

typedef struct
{
    int size;
    int count;
    int head;
    int tail;
    char **lines;
} CircularBuffer;

// function prototypes
bool cbuf_empty(CircularBuffer *cbuf);
bool cbuf_full(CircularBuffer *cbuf);
CircularBuffer *cbuf_create(int size);
void cbuf_free(CircularBuffer *cbuf);

bool cbuf_empty(CircularBuffer *cbuf)
{
    return cbuf->head == cbuf->tail;
}

bool cbuf_full(CircularBuffer *cbuf)
{
    return (cbuf->head - cbuf->tail + cbuf->size) % cbuf->size == 1;
}

CircularBuffer *cbuf_create(int size)
{
    CircularBuffer *cbuf = malloc(sizeof(CircularBuffer));

    if (cbuf == NULL)
    {
        return NULL;
    }

    cbuf->size = size;
    cbuf->count = 0;
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->lines = (char **)malloc(size * sizeof(char *));

    if (cbuf->lines == NULL)
    {
        free(cbuf);
        return NULL;
    }

    return cbuf;
}

void cbuf_free(CircularBuffer *cbuf)
{
    for (int i = 0; i < cbuf->count; i++)
    {
        free(cbuf->lines[(cbuf->head + i) % cbuf->size]);
    }
    free(cbuf->lines);
    free(cbuf);
}

int main(int argc, char **argv)
{
    FILE *file = NULL;
    int num_of_lines = 10;

    for (int i = 1; i < argc; i++)
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

    CircularBuffer *cbuf = cbuf_create(num_of_lines);
    if (cbuf == NULL)
    {
        fprintf(stderr, "Couldn't create circular buffer\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH + 2];
    bool line_too_long_flag = false;

    while (fgets(line, MAX_LINE_LENGTH + 2, file) != NULL)
    {
        if (strlen(line) > MAX_LINE_LENGTH)
        {
            if (!line_too_long_flag)
            {
                fprintf(stderr, "Line too long\n");
                line_too_long_flag = true;
            }
            line[MAX_LINE_LENGTH] = '\n';
            line[MAX_LINE_LENGTH + 1] = '\0';
        }
        // cbuf_put
    }

    // print lines

    cbuf_free(cbuf);

    if (file != stdin && fclose(file) != 0)
    {
        fprintf(stderr, "Couldn't close file\n");
        return 1;
    }

    return 0;
}
