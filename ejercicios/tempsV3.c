/*
 * autor: cristobal liendo i
 * fecha: 9/1/18
 * descripcion: calcula la temperatura maxima, minima y el promedio de
 *              10 datos, sin usar arreglos
*/

#include <stdio.h>

int main() {
    float max, min, avg, val;

    avg = 0;
    for (int i = 0; i < 10; i++) {
        printf("Ingresa la temperatura numero %d: ", i + 1);
        scanf("%f", &val);

        if (i == 0)
            max = min = val;
        else if (val > max)
            max = val;
        else if (val < min)
            min = val;

        avg += val / 10;
    }

    printf("\nEl promedio de las temperaturas es de %.2f\n", avg);
    printf("La temperatura maxima registrada fue: %.2f\n", max);
    printf("La temperatura minima registrada fue: %.2f\n", min);

    return 0;
}

