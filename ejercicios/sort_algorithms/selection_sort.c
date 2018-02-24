/*
 * autor: cristobal liendo i
 * fecha: Tue 20 Feb 2018 06:53:28 PM CST
 * descripcion: selection sort
*/

#include <stdio.h>
#define SIZE(x) (sizeof(x) / sizeof(int))

void swap(int *a, int *b);
void selection_sort(int *a, int length);

int main() {
    int arr[] = {7, -1, 2, 9, -23, 11, 99, -44, -100, 100};

    for (int i = 0; i < SIZE(arr); i++)
        printf("%d, ", arr[i]);

    printf("\n\n");

    selection_sort(arr, SIZE(arr));

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

void selection_sort(int *a, int length) {
    int ac_min;

    for (int i = 0; i < length - 1; i++) {
        ac_min = i;

        for (int j = i; j < length; j++) {
            if (a[j] < a[ac_min])
                ac_min = j;
        }

        if (ac_min != i)
            swap(&a[i], &a[ac_min]);
    }
}
