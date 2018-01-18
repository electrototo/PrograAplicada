/*
 * author: cristobal liendo
 * fecha: 17/01/18
 * descripcion: programa que suma e imprime los multiplos de 3 hasta
 *              el 99
*/

#include <stdio.h>
#define LIMIT 99

int main() {
    // Lo sabemos por la sumatoria de Gauss
    int resultado = (3 * (LIMIT/3) * (LIMIT/3 + 1)) / 2;

    printf("Suma de multiplos del 3 del 3 al 99: %d\n", resultado);

    // Se pone el ciclo porque la indiciacion es imprimir la serie de numeros
    printf("\nMultiplos de 3 del 3 al 99:\n");
    for (int i = 3; i < 100; i += 3)
        printf("%d%s", i, (i == 99) ? "\n\n" : ", ");

    return 0;
}
