/*
 * autor: cristobal liendo i
 * fecha: Thu 15 Feb 2018 05:44:56 PM CST
 * descripcion: Implementacion de merge sort
*/

#include <stdio.h>
#include <stdlib.h>

#define ASIZE(x) (sizeof(x) / sizeof(int))

void merge(int *arr, int p, int q, int l);
void merge_sort(int *arr, int p, int l);

int main() {
    int to_sort[] = {1, -2, -8, 10, 9, 7, -2, -1};

    printf("Original:\n");
    for (int i = 0; i < ASIZE(to_sort); i++)
        printf("Data: %d\n", to_sort[i]);

    printf("\n\n\n");

    merge_sort(to_sort, 0, ASIZE(to_sort) - 1);

    for (int i = 0; i < ASIZE(to_sort); i++)
        printf("Data: %d\n", to_sort[i]);

    return 0;
}

void merge_sort(int *arr, int p, int l) {
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

void merge(int *arr, int p, int q, int l) {
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
