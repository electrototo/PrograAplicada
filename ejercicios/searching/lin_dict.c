/*
 * autor: cristobal liendo i
 * fecha: Tue 27 Feb 2018 07:25:36 PM CST
 * descripcion: binary search
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAMES 370098

int lin_search(char **names, char *v);

void menu();

unsigned int dump_to_array(FILE *fp, char **names);
void dump_to_file(FILE *fp, char **names, unsigned int total);

void dealloc(char **names, unsigned int total);

int main(int argc, char **argv) {
    FILE *fp;
    char filename[100], name[100];

    if (argc < 3) {
        menu();

        return 0;
    }
    else {
        unsigned int total;
        int index;

        fp = fopen(argv[1], "rt");

        char **names = (char **) malloc(sizeof(char *) * MAX_NAMES);

        if (fp == NULL) {
            printf("No se encontro el archivo especificado\n");

            return 1;
        }

        total = dump_to_array(fp, names);
        fclose(fp);

        index = lin_search(names, argv[2]);

        if (index != -1)
            printf("El nombre se encontro en la posicion %d\n", index);
        else
            printf("El nombre no fue encontrado\n");

        dealloc(names, total);
    }

    return 0;
}

void menu() {
    printf("Uso:\n");
    printf("\tnombre_archivo:  nombre del archivo en el que se encuentran las palabras\n");
    printf("\tobjetivo:        palabra a buscar\n");
    printf("\n");
}

unsigned int dump_to_array(FILE *fp, char **names) {
    char buffer[100];
    char **init = names;
    unsigned int total = 0;

    while (!feof(fp) && total < MAX_NAMES) {
        fscanf(fp, "%s ", buffer);
        names[total++] = strdup(buffer);
    }

    if (total >= MAX_NAMES) {
        printf("Mas de %d palabras encontradas...\n", MAX_NAMES);
        printf("Buscando en los primeros %d nombres\n", MAX_NAMES);
    }

    return total;
}

void dealloc(char **names, unsigned int total) {
    for (unsigned int i = 0; i < total; i++)
        free(names[i]);

    free(names);
}

int lin_search(char **names, char *v) {
    unsigned long pos = 0;

    while (pos < MAX_NAMES && strcmp(*names++, v) != 0)
        pos++;

    if (pos == MAX_NAMES)
        pos = -1;

    return pos;
}
