/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: pide 4 numeros e imprime el mayor de los cuatro
*/

#include <stdio.h>

int main() {
    float max, actual;

    for (int i = 0; i < 4; i++) {
        printf("Ingresa un numero: ");
        scanf("%f", &actual);

        if (i == 0 || actual > max)
            max = actual;
    }

    printf("\nEl mayor de todos los numeros fue: %.2f\n", max);

    return 0;
}
