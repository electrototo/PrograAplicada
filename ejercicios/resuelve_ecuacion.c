#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void quitar_enter(char *nombre);

int main() {
    char nombre_archivo[200];
    int a, b, c;
    float r1, r2;

    FILE *archivo;
    
    printf("Dame el nombre del archivo con las ecuaciones: ");
    fgets(nombre_archivo, 199, stdin);
    quitar_enter(nombre_archivo);
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        printf("No existe el archivo. Fin del programa.\n");
        exit(0);
    }

    while (fscanf(archivo, "%d, %d, %d", &a, &b, &c) != EOF) {
        
        r1 = (-b + sqrt(b * b - (4 * a * c))) / (2 * a);
        r2 = (-b - sqrt(b * b - (4 * a * c))) / (2 * a);

        printf("Para %dx^2 + %dx + %d = 0, R1 = %.2f, R2 = %.2f\n", a, b, c, r1, r2);
    }

    fclose(archivo);

    return 0;
}

void quitar_enter(char *nombre) {
    while (*++nombre != '\n');
    *nombre = '\0';
}
