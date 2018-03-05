/*
 * autor: cristobal liendo i
 * fecha: Thu 15 Feb 2018 05:44:56 PM CST
 * descripcion: Implementacion de merge sort
*/

#include <stdio.h>
#include <stdlib.h>

#define ASIZE(x) (sizeof(x) / sizeof(int))

void merge(long int *arr, unsigned long p, unsigned long q, unsigned long l);
void merge_sort(long int *arr, unsigned long p, unsigned long l);

int main(int argc, char **argv) {
    long int total = atol(argv[1]);
    long int *to_sort = calloc(total, sizeof(long int));

    for (long i = 0; i < total; i++)
        to_sort[i] = random() % total;

    printf("Primeros 50 numeros:\n");
    for (int i = 0; i < 50; i++)
        printf("%lu, ", to_sort[i]);

    merge_sort(to_sort, 0, total - 1);

    printf("\nPrimeros 50 numeros ordenados:\n");
    for (int i = 0; i < 50; i++)
        printf("%lu, ", to_sort[i]);

    return 0;
}

void merge_sort(long int *arr, unsigned long p, unsigned long l) {
    int m;

    if (p < l) {
        m = (p + l) / 2;

        // left
        merge_sort(arr, p, m);

        // right
        merge_sort(arr, m + 1, l);

        // merge
        merge(arr, p, m, l);
    }
}

void merge(long int *arr, unsigned long p, unsigned long q, unsigned long l) {
    int i, j, k;
    int s1 = (q - p) + 1;
    int s2 = (l - q);

    int *left = (int *) malloc(sizeof(int) * s1);
    int *right = (int *) malloc(sizeof(int) * s2);

    for (int i = 0; i < s1; i++)
        left[i] = arr[p + i];

    for (int i = 0; i < s2; i++)
        right[i] = arr[q + i + 1];

    i = 0;
    j = 0;
    k = p;
    while (i < s1 && j < s2) {
        if (left[i] < right[j])
            arr[k] = left[i++];
        else
            arr[k] = right[j++];

        k++;
    }

    while (i < s1)
        arr[k++] = left[i++];

    while (j < s2)
        arr[k++] = right[j++];

    free(left);
    free(right);
}
