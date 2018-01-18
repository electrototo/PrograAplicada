/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: programa que intercambia el valor de tres variables
 *              (un poco redundante porque terminamos con las tres
 *               variables con el mismo valor de a, incluyendo a = a)
 */

#include <stdio.h>

int main() {
    float a, b, c;

    printf("Ingresa el valor de a: ");
    scanf("%f", &a);

    printf("Ingresa el valor de b: ");
    scanf("%f", &b);

    printf("Ingresa el valor de c: ");
    scanf("%f", &c);

    b = a;
    c = b;
    a = c;

    printf("\nValor final de a: %.2f\n", a);

    return 0;
}
