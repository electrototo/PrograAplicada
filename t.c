/*
 * autor: cristobal liendo i
 * fecha: Thu 01 Feb 2018 04:27:58 PM CST
 * descripcion: 
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    char *p1, *p2, *p3;

    p1 = (char *) malloc(sizeof(char));
    p2 = (char *) malloc(sizeof(char));
    p3 = (char *) malloc(sizeof(char));

    printf("p1: %p\n", p1);
    printf("p2: %p\n", p2);
    printf("p3: %p\n", p3);

    printf("p1 xor p2: %x\n", p1 ^ p2);

    free(p1);
    free(p2);
    free(p3);

    return 0;
}

