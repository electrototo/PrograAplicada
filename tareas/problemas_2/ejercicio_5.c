/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 12:23:28 PM CST
 *  descripcion: checa si una palabra es palindrome
*/

#include <stdio.h>
#include <string.h>

void normalize(char *string);
void reverse(char *dest, char *src);

char to_lower(char letter);

int main() {
    char normal[300], reversed[300];

    printf("Ingresa la frase que quieras comprobar si es palindrome:\n");
    fgets(normal, 99, stdin);

    normalize(normal);
    reverse(reversed, normal);

    if (strcmp(normal, reversed) == 0)
        printf("\nLa frase es un palindrome\n");
    else
        printf("\nLa frase no es un palindrome\n");

    return 0;
}

char to_lower(char letter) {
    if (letter >= 'a' && letter <= 'z')
        return letter;

    else if(letter >= 'A' && letter <= 'Z')
        return (letter - 'A') + 'a';

    else
        return 7;
}

void normalize(char *string) {
    char c, *current;

    current = string;

    while (*current && *current != '\n') {
        if (*current != ' ') {
            *string = to_lower(*current);
            string++;
        }

        current++;
    }

    *string = '\0';
}

void reverse(char *dest, char *src) {
    int len = strlen(src);

    src = src + len - 1;
    while (len--) {
        *dest++ = *src--;
    }
}
