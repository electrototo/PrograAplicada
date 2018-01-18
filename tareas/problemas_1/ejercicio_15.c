/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion eleva un numero a una poencia real entera positiva
*/

#include <stdio.h>

int main() {
    int number, power, c_power;
    unsigned long res = 1;

    printf("Ingresa el numero: ");
    scanf("%d", &number);

    printf("Ingresa la potencia: ");
    scanf("%d", &power);

    c_power = power;

    while (power-- > 0)
        res *= number;

    printf("\nEl numero %d elevado a %d es %lu\n", number, c_power, res);
}
