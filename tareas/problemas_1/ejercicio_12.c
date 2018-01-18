/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: despliega la suma de 10 numeros usando "variable-acumulador"
*/

#include <stdio.h>

int main() {
    int actual, sum = 0;

    printf("A continuacion ingresa 10 numeros:\n");

    for (int i = 0; i < 10; i++) {
        printf("Ingresa el numero #%d: ", i + 1);
        scanf("%d", &actual);

        sum += actual;
    }

    printf("\nLa suma de los 10 numeros es %d\n", sum);

    return 0;
}
