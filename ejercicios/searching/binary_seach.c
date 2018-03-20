/*
 * autor: cristobal liendo i
 * fecha: Tue 27 Feb 2018 07:25:36 PM CST
 * descripcion: binary search
*/

#include <stdio.h>
#include <stdlib.h>

long bin_search(long *numbers, long v, long l, long r);

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Uso:\n");
        printf("\tnums    cantidad de numeros a generar\n");
        printf("\ttarget  numero a buscar\n");

        return 1;
    }

    long total = atol(argv[1]);
    long target = atol(argv[2]);
    long index;

    long *nums = (long *) malloc(sizeof(long) * total);

    for (long i = 0; i < total; i++)
        nums[i] = i;

    printf("Buscando el numero: %ld\n\n", target);

    index = bin_search(nums, target, 0, total);
    
    if (index != -1)
        printf("El numero %ld se encontro en la posicion %ld\n", target, index);
    else
        printf("%ld no se encuentra en la lista\n", target);

    free(nums);

    return 0;
}

long bin_search(long *numbers, long v, long l, long r) {
    long middle = (l + r) / 2;

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
