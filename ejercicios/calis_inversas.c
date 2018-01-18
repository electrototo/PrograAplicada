/*
 * autor: cristobal liendo i
 * fecha:
 * descripcion: 
*/

#include <stdio.h>

void ask_grades(float *arr, int limit);
void inverse(float *src, float *target, int limit);
void print_table(float *first, float *second, int limit);

int main() {
    float arr1[20], arr2[20];

    ask_grades(arr1, 20);
    inverse(arr1, arr2, 20);
    print_table(arr1, arr2, 20);

    return 0;
}

void ask_grades(float *arr, int limit) {
    for(; limit--; arr++) {
        printf("Ingresa la calificacion del alumno %d: ", 20 - limit);
        scanf("%f", arr);
    }
}

void inverse(float *src, float *target, int limit) {
    float *copy_src, *copy_target;

    copy_target = target + limit - 1;

    while(limit--)
        *(copy_target--) = *(src++);
}

void print_table(float *first, float *second, int limit) {
    printf("\nPrimer arreglo  Segundo arreglo\n");
    
    while (limit--)
        printf("    %05.2f            %05.2f\n", *first++, *second++);
}
