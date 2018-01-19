/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 11:39:06 AM CST
 *  descripcion:  separa palabras de una frase y luego imprime las palabras
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WMAX 100

char *alloc_word(char *word);
char getword(char *word, int max_size);
int is_letter(char letter);

int main() {
    char c_word[50], *words[WMAX], c;
    int index = 0;

    printf("Ingresa una frase:\n");

    while ((c = getword(c_word, 50)) != '\n')
        if (is_letter(c))
            words[index++] = alloc_word(c_word);

    printf("\nPalabras linea por linea:\n");
    for (int i = 0; i < index; i++)
        printf("\t[%d] %s\n", i + 1, words[i]);

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

char *alloc_word(char *word) {
    char *new_pos = (char *) malloc(strlen(word) + 1);

    strcpy(new_pos, word);

    return new_pos;
}

int is_letter(char letter) {
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}
