/*
 * autor: cristobal liendo i
 * fecha: Tue 20 Feb 2018 07:28:02 PM CST
 * descripcion: quicksort
*/

#include <stdio.h>
#include <stdlib.h>

void quicksort(int *a, int left, int right);
int partition(int *a, int left, int right);
void swap(int *a, int *b);

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

    printf("\n\nOrdenando con quicksort sort...\n");

    quicksort(numbers_1, 0, total);

    printf("\nPrimeros 50 numeros ordenados:\n");
    for (int i = 0; i < 50; i++)
        printf("%d, ", numbers_1[i]);

    free(numbers_1);

    return 0;
}

void quicksort(int *a, int left, int right) {
    int pi;

    if (left < right) {
        pi = partition(a, left, right);

        quicksort(a, left, pi - 1);
        quicksort(a, pi + 1, right);
    }
}

int partition(int *a, int left, int right) {
    int pi = a[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (a[j] < pi) {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[right]);

    return i + 1;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
