/*
 * autor: cristobal liendo
 * fecha: 17/1/18
 * descripcion: indica si dos caracteres se encuentran en orden alfabetico
 *              o no
*/

#include <stdio.h>

int is_letter(char s);
char to_lower(char s);

int main() {
    char string[2], valid = 1;

    printf("Ingresa dos letras: ");
    fgets(string, 3, stdin);

    for(int i = 0; i < 2; i++) {
        string[i] = to_lower(string[i]);
        
        if (string[i] == 0)
            valid = 0;
    }

    if(string[0] > string[1] && valid)
        printf("\nLas letras %s no se encuentran en orden alfabetico\n", string);

    else if (string[0] <= string[1] && valid)
        printf("\nLas letras %s se encuentran en orden alfabetico\n", string);

    else
        printf("\nLos caracteres que se ingresaron son invalidos o insuficientes\n");

    return 0;
}

int is_letter(char s) {
    return (s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z');
}

char to_lower(char s) {
    if (is_letter(s)) {
        if (s >= 'a' && s <= 'z')
            return s;
        else
            return (s - 'A') + 'a';
    }

    else
        return 0;
}
