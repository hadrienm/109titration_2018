/*
** EPITECH PROJECT, 2019
** titration
** File description:
** titration
*/

#include "my.h"

static void check_syntax_buffer2(char *line, FILE *stream)
{
    if (line[0] == ';') {
        write(2, "input error\n", 12);
        free(line);
        fclose(stream);
        exit (84);
    }
    if (line[0] == '.') {
        write(2, "input error\n", 12);
        free(line);
        fclose(stream);
        exit (84);
    }
}

static void check_syntax_buffer(char *line, FILE *stream)
{
    for (int a = 0; line[a] != '\0'; a++) {
        if (line[a] == ';' && (line[a + 1] == '\0' ||
            line[a + 1] == '\n' || line[a + 1] == '.')) {
            write(2, "input error\n", 12);
            free(line);
            fclose(stream);
            exit (84);
        }
        if (line[a] == '.' && (line[a + 1] == ';' ||
            line[a + 1] == '\0' || line[a + 1] == '\n')) {
            write(2, "input error\n", 12);
            free(line);
            fclose(stream);
            exit (84);
        }
        check_syntax_buffer2(line, stream);
    }
}

static void check_buffer(char *buffer, FILE *stream)
{
    int semi_coma = 0;
    int point = 0;

    for (int a = 0; buffer[a]; a++) {
        if (buffer[a] == '.')
            point++;
        if (buffer[a] == ';')
            semi_coma++;
    }
    if (semi_coma > 1 || point > 2) {
        write(2, "input error\n", 12);
        free(buffer);
        fclose(stream);
        exit (84);
    }
    check_syntax_buffer(buffer, stream);
}

static void condition(char *line, int a, FILE *stream)
{
    if (line[a] < 48 || line[a] > 57) {
        if (line[a] != 46 && line[a] != 59 &&
            line[a] != '\n' && line[a] != '\0') {
            write(2, "the data base is false\n", 23);
            free(line);
            fclose(stream);
            exit (84);
        }
    } else {
        check_buffer(line, stream);
    }
}

void verification(char *av)
{
    static int c = 0;
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    stream = fopen(av, "r");
    while ((nread = getline(&line, &len, stream) != -1))
        for (int a = 0; line[a] != '\0'; a++) {
            condition(line, a, stream);
            c++;
        }
    if (c == 0) exit(84);
    free(line);
    fclose(stream);
}