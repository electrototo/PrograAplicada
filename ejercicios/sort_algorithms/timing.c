/*
 * autor: cristobal liendo i
 * fecha: Thu 22 Feb 2018 04:20:54 PM CST
 * descripcion:  timing between bubble sort and quicksort
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void swap(int *a, int *b);
void bubble_sort(int *arr, int length);
void quicksort(int *a, int left, int right);
int partition(int *a, int left, int right);

unsigned long long diff_time(struct timespec *start, struct timespec *stop);

int main(int arg, char **argv) {
    int total = atoi(argv[1]);

    int randint;

    int *numbers_1 = calloc(total, sizeof(int));
    int *numbers_2= calloc(total, sizeof(int));

    struct timespec start, stop;

    srand(time(NULL));

    if (total < 50)  {
        printf("Debe ser mayor a 50 numeros...\n");

        return 0;
    }

    for (int i = 0; i < total; i++) {
        randint = random() % total;
        numbers_1[i] = randint;
        numbers_2[i] = randint;
    }

    printf("Primeros 50 numeros:\n");
    for (int i = 0; i < 50; i++)
        printf("%d, ", numbers_1[i]);

    printf("\n\nOrdenando con bubble sort...\n");

    clock_gettime(CLOCK_MONOTONIC, &start);
    bubble_sort(numbers_1, total);
    clock_gettime(CLOCK_MONOTONIC, &stop);

    printf("\nTiempo demorado en ordenar %d numeros (bubble sort):\n", total);
    printf("  milisegundos:    %llu ms\n", (long long) (diff_time(&start, &stop) / 1e3));
    printf("  segundos:        %llu s\n", diff_time(&start, &stop));

    printf("\nPrimeros 50 numeros ordenados:\n");
    for (int i = 0; i < 50; i++)
        printf("%d, ", numbers_1[i]);

    printf("\n\nOrdenando con quicksort...\n");

    clock_gettime(CLOCK_MONOTONIC, &start);
    quicksort(numbers_2, 0, total);
    clock_gettime(CLOCK_MONOTONIC, &stop);

    printf("\nTiempo demorado en ordenar %d numeros (quicksort):\n", total);
    printf("  milisegundos:    %llu ms\n", diff_time(&start, &stop));
    printf("  segundos:        %llu s\n", (long long) (diff_time(&start, &stop) / 1e3));

    printf("\nPrimeros 50 numeros ordenados:\n");
    for (int i = 0; i < 50; i++)
        printf("%d, ", numbers_2[i + 1]);

    printf("\n");

    free(numbers_1);
    free(numbers_2);

    return 0;
}

void bubble_sort(int *arr, int length) {
    for (int i = 0; i < length - 1; i++)
        for (int j = 0; j < length - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
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

unsigned long long diff_time(struct timespec *start, struct timespec *stop) {
    long ms = (stop->tv_nsec / 1e6) - (start->tv_nsec / 1e6);

    return ms;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
