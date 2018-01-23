/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 11:22:48 AM CST
 *  descripcion: pide al usuario una frase y posteriormente imprime la frecuencia
 *               de cada letra en la frase. Case insensitive
*/

#include <stdio.h>

void get_frequency(int *frequency_list);
char to_lower(char letter);

int main() {
    static int frequency[26];

    printf("Ingresa una frase: ");
    get_frequency(frequency);

    printf("\nFrecuencia de las letras que aparecen en la frase:\n");
    for (int i = 0; i < 26; i++)
        if (frequency[i] > 0)
            printf("\t%c: %d\n", 'a' + i, frequency[i]);

    return 0;
}

void get_frequency(int *frequency_list) {
    char c;

    while ((c = getchar()) != '\n' && c != EOF) {
        c = to_lower(c);

        if (c != 7)
            frequency_list[c - 'a']++;
    }
}

char to_lower(char letter) {
    if (letter >= 'a' && letter <= 'z')
        return letter;

    else if(letter >= 'A' && letter <= 'Z')
        return (letter - 'A') + 'a';

    else
        return 7;
}
