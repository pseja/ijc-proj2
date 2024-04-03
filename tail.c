#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
char *duplicate_string(char *line);
void cbuf_put(CircularBuffer *cbuf, char *line);
char *cbuf_get(CircularBuffer *cbuf, int index);
void cbuf_print(CircularBuffer *cbuf);

bool cbuf_empty(CircularBuffer *cbuf)
{
    return cbuf->count == 0;
}

bool cbuf_full(CircularBuffer *cbuf)
{
    return cbuf->count == cbuf->size;
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

char *duplicate_string(char *line)
{
    char *str = malloc(strlen(line) + 1);
    if (str == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for duplicate string\n");
        return NULL;
    }
    strcpy(str, line);
    return str;
}

void cbuf_put(CircularBuffer *cbuf, char *line)
{
    if (cbuf_full(cbuf))
    {
        free(cbuf->lines[cbuf->head]);
        cbuf->head = (cbuf->head + 1) % cbuf->size;
        cbuf->count--;
    }
    cbuf->lines[cbuf->tail] = duplicate_string(line);
    cbuf->tail = (cbuf->tail + 1) % cbuf->size;
    cbuf->count++;
}

char *cbuf_get(CircularBuffer *cbuf, int index)
{
    if (index < 0 || index >= cbuf->count)
    {
        return NULL;
    }
    return cbuf->lines[(cbuf->head + index) % cbuf->size];
}

void cbuf_print(CircularBuffer *cbuf)
{
    for (int i = 0; i < cbuf->count; i++)
    {
        printf("%s", cbuf_get(cbuf, i));
    }
    printf("\n");
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
    }

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
        cbuf_put(cbuf, line);
    }

    cbuf_print(cbuf);

    cbuf_free(cbuf);

    if (file != stdin && fclose(file) != 0)
    {
        fprintf(stderr, "Couldn't close file\n");
        return 1;
    }

    return 0;
}
