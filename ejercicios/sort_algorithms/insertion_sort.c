/*
 * autor: cristobal liendo i
 * fecha: Tue 20 Feb 2018 06:25:52 PM CST
 * descripcion: insertion sort
*/

#include <stdio.h>
#define SIZE(x) (sizeof(x) / sizeof(int))

void insertion_sort(int *arr, int length);
void swap(int *a, int *b);

int main() {
    int arr[] = {7, -1, 2, 9, -23, 11, 99, -44, -100, 100};

    for (int i = 0; i < SIZE(arr); i++)
        printf("%d, ", arr[i]);

    printf("\n\n");

    insertion_sort(arr, SIZE(arr));

    for (int i = 0; i < SIZE(arr); i++)
        printf("%d, ", arr[i]);

    printf("\n");

    return 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion_sort(int *arr, int length) {
    int j;

    for (int i = 1; i < length; i++) {
        j = i;

        while(arr[j] < arr[j - 1] && j > 0) {
            swap(&arr[j], &arr[j - 1]);
            j--;
        }
    }
}
