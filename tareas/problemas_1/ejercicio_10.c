/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: calcula de manera independiente la suma de los numeros
 *              pares e impares comprendidos entre 1 y 200
 *              (lo calcula utilizando la suma de gauss, lo cual lo convierte
 *               en un programa que se ejecuta en tiempo constante)
*/

#include <stdio.h>
#define MAX 200

int main() {
    int odd, even;

    even = (MAX / 2) * (MAX / 2 + 1);
    odd = (MAX / 2) * (MAX / 2);
    
    printf("Suma de los pares del 1 al %d: %d\n", MAX, even);
    printf("Suma de los impares del 1 al %d: %d\n", MAX, odd);

    return 0;
}
