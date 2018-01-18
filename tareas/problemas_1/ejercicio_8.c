/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: determina si una letra ingresada por el usuario
 *              es mayuscula o minuscula
*/

#include <stdio.h>

int main() {
    char l;

    printf("Ingresa una letra: ");
    l = getchar();

    if (l >= 'A' && l <= 'Z')
        printf("\nLa letra %c es mayuscula\n", l);

    else if (l >= 'a' && l <= 'z')
        printf("\nLa letra %c es minuscula\n", l);

    else
        printf("\nEl caracter ingresado no es una letra\n");

    return 0;
}
