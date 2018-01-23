/*
 *  autor: cristobal liendo i
 *  fecha: Sat 20 Jan 2018 01:14:01 PM CST
 *  descripcion: Hace mayusuculas la primera y ultima letra de una palabra
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char capsize(char letter);
char getword(char *word, int max_size);
int is_letter(char letter);

int main() {
    unsigned char buffer[30], last, start = 1;

    printf("Ingresa una frase:\n\t");
    while (getword(buffer, 30) != '\n') {
        if (start) {
            printf("\nFrase modificada:\n\t");
            start = 0;
        }

        last = strlen(buffer);

        buffer[0] = capsize(buffer[0]);
        buffer[last - 1] = capsize(buffer[last - 1]);

        printf("%s ", buffer);
    }

    printf("\n");

    return 0;
}

char getword(char *word, int max_size) {
    char c;

    while ((c = getchar()) == ' ' || c == '\t');

    if (!(is_letter(c)))
        return c;
    else
        ungetc(c, stdin);

    while ((c = getchar()) != EOF && is_letter(c) && max_size-- != 1)
        if (is_letter(c))
            *word++ = c;

    ungetc(c, stdin);

    *word = '\0';

    return *(word - 1);
}

int is_letter(char letter) {
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}

char capsize(char letter) {
    if (letter >= 'A' && letter <= 'Z')
        return letter;
    else if (letter >= 'a' && letter <= 'z')
        return (letter - 'a') + 'A';
    else
        return letter;
}
