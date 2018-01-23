/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 01:32:43 PM CST
 *  descripcion: convierte una oracion en mayusculas
*/

#include <stdio.h>

char capsize(char letter);
char smallcap(char letter);

int main() {
    char c, buffer[200], size = 0;

    printf("Ingresa una frase: ");

    while ((c = getchar()) != '\n' && c != EOF && size < 200)
        buffer[size++] = c;

    printf("\nEn mayusculas:\n\t");

    for (int i = 0; i < size; i++)
        printf("%c", capsize(buffer[i]));

    printf("\n\nEn minusculas:\n\t");

    for (int i = 0; i < size; i++)
        printf("%c", smallcap(buffer[i]));

    printf("\n");

    return 0;
}

char capsize(char letter) {
    if (letter >= 'A' && letter <= 'Z')
        return letter;
    else if (letter >= 'a' && letter <= 'z')
        return (letter - 'a') + 'A';
    else
        return letter;
}

char smallcap(char letter) {
    if (letter >= 'a' && letter <= 'z')
        return letter;
    else if (letter >= 'A' && letter <= 'Z')
        return (letter - 'A') + 'a';
    else
        return letter;
}
