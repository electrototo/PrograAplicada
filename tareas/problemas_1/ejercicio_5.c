/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: calcula el area de un triangulo como funcion de
 *              su base y altura
*/

#include <stdio.h>

int main() {
    float base, height;

    printf("Ingresa la base del triangulo: ");
    scanf("%f", &base);

    printf("Ingresa la altura del triangulo: ");
    scanf("%f", &height);

    printf("\nEl triangulo tiene una superficie de %.2f unidades cuadradas\n", (base * height) / 2);

    return 0;
}
