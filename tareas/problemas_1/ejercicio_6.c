/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: obtiene el peso de una persona en libras e imprime su peso
 *              en kg y g.
 *              (es de mucha utilidad para los humanos que no usen el S.I.)
*/

#include <stdio.h>

int main() {
    float weight, conversion_f;

    conversion_f = 0.453592;

    printf("Ingresa el peso de la persona (en libras): ");
    scanf("%f", &weight);

    printf("\nLa persona pesa %.2f kilogramos y %.2f gramos\n",
           weight * conversion_f, weight * conversion_f * 1000);

    return 0;
}
