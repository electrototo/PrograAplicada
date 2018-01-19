/*
 * autor: cristobal liendo
 * fecha: 19/01/18
 * descripcion: calcula el cuadrado de los 100 primeros numeros e imprime la tabla
*/

#include <stdio.h>

void square(int *);
void print_table(int *);

int main() {
    int cuadrados[100];

    square(cuadrados);
    print_table(cuadrados);

    return 0;
}

void square(int *arr) {
    for (int i = 0; i < 100; i++)
        arr[i] = (i + 1) * (i + 1);
}

void print_table(int *arr) {
    printf("|   x    |     x^2   |\n");
    for (int i = 0; i < 100; i++)
        printf("|   %3d  |  %5d    |\n", i + 1, arr[i]);
}
