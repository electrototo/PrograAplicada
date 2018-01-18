/*
 * autor: cristobal liendo i
 * fecha: 9/1/11 vim
 * descripcion: calcula la temperatura maxima, minima y el promedio de
 *              10 datos usando arreglos.
*/

#include <stdio.h>

int main() {
    float avg, min, max;
    float vals[10];

    avg = 0;

    for (int i = 0; i < 10; i++) {
        printf("Ingresa la temperatura numero %d: ", i + 1);
        scanf("%f", &vals[i]);

        if (i == 0){
            max = vals[i];
            min = vals[i];
        }

        else if (vals[i] > max)
            max = vals[i];

        else if (vals[i] < min)
            min = vals[i];

        avg += vals[i] / 10;
    }

    printf("\nEl promedio de las temperaturas fue: %.2f\n", avg);
    printf("La temperatura mayor fue: %.2f\n", max);
    printf("La temperatura menor fue: %.2f\n", min);

    return 0;
}
