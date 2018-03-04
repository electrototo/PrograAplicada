/*
 * autor: cristobal liendo i
 * fecha: Tue 27 Feb 2018 07:25:36 PM CST
 * descripcion: binary search
*/

#include <stdio.h>
#define ARR_SIZE(x) (sizeof(x) / sizeof(int))

int bin_search(int *numbers, int v, int l, int r);

int main() {
    int nums[] = {1, 3, 5, 6, 8, 10, 13, 22, 33, 55};

    for (int i = 0; i < ARR_SIZE(nums); i++)
        printf("[%d] %d\n", i, nums[i]);

    printf("Searching for 8: %d\n", bin_search(nums, 8, 0, ARR_SIZE(nums)));
    printf("Searching for 100: %d\n", bin_search(nums, 100, 0, ARR_SIZE(nums)));
    printf("Searching for 55: %d\n", bin_search(nums, 55, 0, ARR_SIZE(nums)));
    printf("Searching for 1: %d\n", bin_search(nums, 1, 0, ARR_SIZE(nums)));

    return 0;
}

int bin_search(int *numbers, int v, int l, int r) {
    int middle = (l + r) / 2;

    if (l <= r) { 
        if (numbers[middle] == v)
            return middle;

        else if (numbers[middle] < v)
            return bin_search(numbers, v, middle + 1, r);

        else
            return bin_search(numbers, v, l, middle - 1);
    }

    return -1;
}
