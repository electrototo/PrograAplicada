/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 12:43:05 PM CST
 *  descripcion: invierte el orden de las palabras en una frase
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WMAX 100

char *alloc_word(char *word);
char getword(char *word, int max_size);
int is_letter(char letter);

void swap(char **src, char **dst);
void reverse(char **src, int items);

int main() {
    char c_word[50], *words[WMAX], c;
    int index = 0;

    printf("Ingresa una frase para invertirla:\n");

    while ((c = getword(c_word, 50)) != '\n')
        if (is_letter(c))
            words[index++] = alloc_word(c_word);

    reverse(words, index);

    printf("\nFrase invertida:\n");
    for (int i = 0; i < index; i++)
        printf("%s%c", words[i], (i == index - 1) ? '\n': ' ');

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

void swap(char **src, char **dst) {
    char *tmp;

    tmp = *src;
    *src = *dst;
    *dst = tmp;
}

void reverse(char **src, int items) {
    char **end = src + items - 1;

    for (int i = 0; i < (items / 2); i++, src++, end--)
        swap(src, end);
}
