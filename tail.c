// Lukáš Pšeja (xpsejal00)
// Fakulta informačních technologií Vysokého učení technického v Brně
// Příklad: 1
// 23.4.2024

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 2047

// error codes
#define ERR_ARGS 1
#define ERR_FILE 2
#define ERR_INTENDED_EXIT -1

typedef struct
{
    FILE *file;
    int num_of_lines;
} Arguments;

typedef struct
{
    int size;
    int head;
    int tail;
    char **lines;
} CircularBuffer;

// function prototypes
int handle_arguments(Arguments *args, int argc, char **argv);
bool cbuf_empty(CircularBuffer *cbuf);
bool cbuf_full(CircularBuffer *cbuf);
CircularBuffer *cbuf_create(int size);
void cbuf_free(CircularBuffer *cbuf);
void cbuf_put(CircularBuffer *cbuf, char *line);
char *cbuf_get(CircularBuffer *cbuf, int index);
void cbuf_print(CircularBuffer *cbuf);

int handle_arguments(Arguments *args, int argc, char **argv)
{
    args->file = NULL;
    args->num_of_lines = 11; // one extra element for checking if queue is full

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Invalid amount of arguments\n");
                return ERR_ARGS;
            }

            i++;

            if (strspn(argv[i], "0123456789") != strlen(argv[i]))
            {
                fprintf(stderr, "-n [NUMBER] - NUMBER is not a valid number\n");
                return ERR_ARGS;
            }

            args->num_of_lines = atoi(argv[i]);

            if (args->num_of_lines == 0)
            {
                return ERR_INTENDED_EXIT;
            }

            args->num_of_lines++; // increment value by one to make room for checking if queue is full
        }
        else if (args->file == NULL)
        {
            args->file = fopen(argv[i], "r");

            if (args->file == NULL)
            {
                fprintf(stderr, "Couldn't open file %s\n", argv[i]);
                return ERR_FILE;
            }

            // check if file is empty
            int c = fgetc(args->file);
            if (c == EOF)
            {
                return ERR_INTENDED_EXIT;
            }
            else
            {
                ungetc(c, args->file);
            }
        }
        else
        {
            fprintf(stderr, "Invalid amount of arguments\n");
            return ERR_ARGS;
        }
    }

    if (args->file == NULL)
    {
        args->file = stdin;
    }

    return 0;
}

bool cbuf_empty(CircularBuffer *cbuf)
{
    return cbuf->head == cbuf->tail;
}

bool cbuf_full(CircularBuffer *cbuf)
{
    return (cbuf->tail + 1) % cbuf->size == cbuf->head;
}

CircularBuffer *cbuf_create(int size)
{
    CircularBuffer *cbuf = malloc(sizeof(CircularBuffer));

    if (cbuf == NULL)
    {
        return NULL;
    }

    cbuf->size = size;
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
    int count = (cbuf->tail - cbuf->head + cbuf->size) % cbuf->size;

    for (int i = 0; i < count; i++)
    {
        free(cbuf->lines[(cbuf->head + i) % cbuf->size]);
    }
    free(cbuf->lines);
    free(cbuf);
}

void cbuf_put(CircularBuffer *cbuf, char *line)
{
    if (cbuf_full(cbuf))
    {
        free(cbuf->lines[cbuf->head]);
        cbuf->head = (cbuf->head + 1) % cbuf->size;
    }
    cbuf->lines[cbuf->tail] = strdup(line);
    cbuf->tail = (cbuf->tail + 1) % cbuf->size;
}

char *cbuf_get(CircularBuffer *cbuf, int index)
{
    int count = (cbuf->tail - cbuf->head + cbuf->size) % cbuf->size;

    if (index < 0 || index >= count)
    {
        return NULL;
    }

    return cbuf->lines[(cbuf->head + index) % cbuf->size];
}

void cbuf_print(CircularBuffer *cbuf)
{
    int count = (cbuf->tail - cbuf->head + cbuf->size) % cbuf->size;

    for (int i = 0; i < count; i++)
    {
        printf("%s", cbuf_get(cbuf, i));
    }
    printf("\n");
}

void read_lines(CircularBuffer *cbuf, FILE *file, unsigned max_line_length)
{
    char line[max_line_length + 2];
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
}

int main(int argc, char **argv)
{
    Arguments args;
    int err = handle_arguments(&args, argc, argv);

    if (err == ERR_INTENDED_EXIT)
    {
        return 0;
    }
    else if (err != 0)
    {
        return err;
    }

    CircularBuffer *cbuf = cbuf_create(args.num_of_lines);

    if (cbuf == NULL)
    {
        fprintf(stderr, "Couldn't create circular buffer\n");
        return 1;
    }

    read_lines(cbuf, args.file, MAX_LINE_LENGTH);

    cbuf_print(cbuf);

    cbuf_free(cbuf);

    if (args.file != stdin && fclose(args.file) != 0)
    {
        fprintf(stderr, "Couldn't close file\n");
        return ERR_FILE;
    }

    return 0;
}
