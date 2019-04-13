/*
** EPITECH PROJECT, 2019
** titration
** File description:
** titration
*/

#include "my.h"

int verify_h(char *str)
{
    if (strlen(str) == 2 && str[0] == '-' && str[1] == 'h') {
        printf("USAGE\n    ./109titration file\n\nDESCRIPTION\n    file    a csv file containing “vol;ph” lines\n");
        return 0;
    }
    return 1;
}

int cant_open(char *str)
{
    int fd = open(str, O_RDONLY);
    return fd;
}

void print_array(char **save)
{
    for (int i = 0; save[i] != NULL; i++)
        printf("%s\n", save[i]);
}

char *cpy_simple(char *str)
{
    int i = 0;
    char *str2 = malloc(sizeof(char) * (strlen(str) + 1));
    for (; str[i] != '\0'; i++)
        str2[i] = str[i];
    str2[i] = '\0';
    return str2;
}

double transform(char *save)
{
    char *str = NULL;
    int i = 0;
    int k = 0;
    for (; save[i] != '\0' && save[i] != ';' ; i++);
    str = malloc(sizeof(char) * (i + 1));
    for (; k != i; k++)
        str[k] = save[k];
    str[k] = '\0';
    return atof(str);
}

double transform_2(char *save)
{
    char *str = NULL;
    int i = 0;
    int k = 0;
    int save2 = 0;
    for (; save[i] != '\0'; i++);
    for (; save[i] != ';'; i--);
    i++;
    save2 = i;
    for (k = i; save[k] != '\0'; k++)
    str = malloc(sizeof(char) * (k - i + 1));
    for (k = 0; save[save2] != '\0'; ++save2, k++)
        str[k] = save[save2];
    return atof(str);
}

void calcul_second_deriv(double **resu, double *trans, int i)
{
    double save = 0;
    for (int j = 1; j < i - 4; ++j) {
        save = (trans[j + 1] - trans[j - 1]);
        save /= (resu[j + 2][0] - resu[j][0]);
        printf("%0.2lf %0.2f\n", resu[j + 1][0], save);
    }
}

void find_point(double **resu, double *trans, int i)
{
    double save = 0;
    int resultat = 0;
    for (int j = 1; j != i - 1; ++j) {
        if (save < trans[j]) {
            save = trans[j];
            resultat = j;
        }
    }
    printf("resultat %f\n", resu[resultat+1][0]);
    calcul_second_deriv(resu, trans, i);
}

void calcul(char **save)
{
    int i = 0;
    for (; save[i] != NULL; i++);
    double *trans = malloc(sizeof(double) * (i + 1));
    double **resu = malloc(sizeof(double *) * (i + 1));
    for (i = 0; save[i] != NULL; i++) {
        resu[i] = malloc(sizeof(double) * (3));
        resu[i][0] = transform(save[i]);
        resu[i][1] = transform_2(save[i]);
    }
    for (int j = 1, k = 0; j < i - 1; j++, k++) {
        trans[k] = resu[j + 1][1] - resu[j - 1][1];
        trans[k] /= (resu[j + 1][0] - resu[j - 1][0]);
        printf("%0.2lf\n", trans[k]);
    }
    find_point(resu, trans, i);
}

char *my_strcpy(char *str)
{
    size_t i = 0;
    char *save = malloc(sizeof(char) * (strlen(str) + 1));
    for (; i != strlen(str); i++)
        save[i] = str[i];
    save[i] = '\0';
    return save;
}

int main(int ac, char **av)
{
    char **save = NULL;
    char *buff = NULL;
    int i = 0;
    FILE *stream;
    size_t nb = 20;
    if (ac < 2)return 84;
    if (ac == 2 && verify_h == 0)return 0;
    if (cant_open(av[1]) == -1) {
        write(2,"input error\n", 12);
        return 84;
    }
    verification(av[1]);
    stream = fopen(av[1], "r");
    for (; getline(&buff, &nb, stream) != -1; i++);
    save = malloc(sizeof(char *) * (i + 1));
    stream = fopen(av[1], "r");
    for (i = 0; getline(&buff, &nb, stream) != -1; i++) {
        save[i] = my_strcpy(buff);
    }
    save[i] = NULL;
    calcul(save);
}