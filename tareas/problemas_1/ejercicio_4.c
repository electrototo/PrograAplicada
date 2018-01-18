/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: determina si un numero "n" es primo
*/

#include <stdio.h>
#include <math.h>

int is_prime(int number);

int main() {
    int number;

    printf("Ingresa un numero entero: ");
    scanf("%d", &number);

    if (is_prime(number))
        printf("\nEl numero %d es primo\n", number);

    else
        printf("\nEl numero %d no es primo\n", number);

    return 0;
}

int is_prime(int number) {
    int prime = 1;

    if (number > 2)
        for (int i = 2; i < (sqrt(number) + 1) && prime; i++) {
            if (number % i == 0)
                prime = 0;
        }

    else if (number != 2)
        prime = 0;

    return prime;
}
