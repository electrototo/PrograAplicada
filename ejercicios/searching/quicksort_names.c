/*
 * autor: cristobal liendo i
 * fecha: Tue 27 Feb 2018 14:27:02 PM CST
 * descripcion: ordena nombres en un archvio quicksort
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMES 100

void quicksort(char **a, int left, int right);
int partition(char **a, int left, int right);
void swap(char **a, char **b);

void menu(char *filename);
unsigned int dump_to_array(FILE *fp, char **names);
void dump_to_file(FILE *fp, char **names, unsigned int total);

void dealloc(char **names, unsigned int total);

int main(int argc, char **argv) {
    FILE *fp;
    char filename[100];

    unsigned int total;

    menu(filename);
    fp = fopen(filename, "rt");

    char **names = (char **) malloc(sizeof(char *) * MAX_NAMES);

    if (fp == NULL) {
        printf("No se encontro el archivo especificado\n");

        return 1;
    }

    total = dump_to_array(fp, names);
    fclose(fp);

    printf("Total de nombres encontrados: %d\n", total);

    quicksort(names, 0, total - 1);

    strcpy(filename, "ordenados.txt");
    printf("Guardando los nombres ordenados en %s\n", filename);

    fp = fopen(filename, "wt");
    dump_to_file(fp, names, total);
    fclose(fp);

    return 0;
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
        printf("Ordenando los primeros %d nombres\n", MAX_NAMES);
    }

    return total;
}

void dump_to_file(FILE *fp, char **names, unsigned int total) {
    for (unsigned int i = 0; i < total; i++)
        fprintf(fp, "%s\n", names[i]);
}

void dealloc(char **names, unsigned int total) {
    for (unsigned int i = 0; i < total; i++)
        free(names[i]);

    free(names);
}

void menu(char *filename) {
    printf("Ordena nombres de un archivo\n");
    printf("\nIngresa el nombre del archivo: ");
    scanf("%s", filename);
}

void quicksort(char **a, int left, int right) {
    int pi;

    if (left < right) {
        pi = partition(a, left, right);

        quicksort(a, left, pi - 1);
        quicksort(a, pi + 1, right);
    }
}

int partition(char **a, int left, int right) {
    char *pi = a[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (strcmp(a[j], pi) < 0) {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[right]);

    return i + 1;
}

void swap(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}
