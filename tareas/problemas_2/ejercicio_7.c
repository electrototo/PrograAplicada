/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 01:26:02 PM CST
 *  descripcion: imprime las palabras del extremo, ignorando espacios y la
 *               de en medio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *alloc_word(char *word);
char getword(char *word, int max_size);
int is_letter(char letter);

int main() {
    char word_1[100], word_2[100], word_3[100];

    printf("Ingresa una frase de tres palabras: ");

    getword(word_1, 100);
    getword(word_2, 100);
    getword(word_3, 100);

    printf("\nLa frase sin la palabra de en medio es: ");
    printf("%s %s\n", word_1, word_3);

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
