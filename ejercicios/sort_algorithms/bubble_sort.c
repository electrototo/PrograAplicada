/*
 * autor: cristobal liendo i
 * fecha: Tue 20 Feb 2018 05:14:26 PM CST
 * descripcion: bubble sort
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);
void bubble_sort(int *arr, int length);

int main(int argc, char **argv) {
    int total = atoi(argv[1]);
    int randint;

    int *numbers_1 = calloc(total, sizeof(int));

    for (int i = 0; i < total; i++) {
        randint = random() % total;
        numbers_1[i] = randint;
    }

    printf("Primeros 50 numeros:\n");
    for (int i = 0; i < 50; i++)
        printf("%d, ", numbers_1[i]);

    printf("\n\nOrdenando con bubble sort...\n");

    bubble_sort(numbers_1, total);

    printf("\nPrimeros 50 numeros ordenados:\n");
    for (int i = 0; i < 50; i++)
        printf("%d, ", numbers_1[i]);

    free(numbers_1);

    return 0;
}
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int *arr, int length) {
    for (int i = 0; i < length - 1; i++)
        for (int j = 0; j < length - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}
