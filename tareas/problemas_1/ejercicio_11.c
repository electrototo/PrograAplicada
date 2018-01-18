/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: lee una serie denumeros e indica cual es el mayor
*/

#include <stdio.h>

int main() {
    int sum = 0, actual = 0;

    printf("Ingresa a continuacion los numeros que deseas sumar, indicando con el numero -99 el final de la serie\n");
    printf("Los numeros menores a 0 seran descartados\n\n");

    while (actual != -99) {
        printf("Ingresa un numero: ");
        scanf("%d", &actual);

        if (actual != -99 && actual > 0)
            sum += actual;
    }

    printf("\nLa suma de los numeros es %d\n", sum);

    return 0;
}
