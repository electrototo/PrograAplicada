/*
 * autor: cristobal liendo i
 * fecha: 9/1/11
 * descripcion: calcula la temperatura maxima, minima y el promedio de
 *              10 datos, sin usar arreglos, pero usando apuntadores
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    float avg, min, max;
    float *vals, *tmp;

    vals = (float *) malloc(sizeof(float) * 10);

    tmp = vals;
    avg = 0;

    for (int i = 0; i < 10; i++, tmp++) {
        printf("Ingresa el numero %d: ", i + 1);
        scanf("%f", tmp);

        if (i == 0)
            max = min = *tmp;

        else if (*tmp > max)
            max = *tmp;

        else if (*tmp < min)
            min = *tmp;

        avg += *tmp / 10;
    }

    printf("\nEl promedio de las temperaturas fue: %.2f\n", avg);
    printf("La temperatura maxima registrada fue: %.2f\n", max);
    printf("La temperatura minima registrada fue: %.2f\n", min);

    free(vals);

    return 0;
}
