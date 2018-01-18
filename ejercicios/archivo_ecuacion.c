#include <stdio.h>
#include <string.h>

void pedir_nombre_archivo(char *nombre_archivo);
void pedir_ecuaciones(int m_coef[5][3]);
void quitar_enter(char *nombre);

int main() {
    FILE *archivo;
    char nombre_archivo[200];
    int m_coef[5][3];

    pedir_nombre_archivo(nombre_archivo);
    archivo = fopen(nombre_archivo, "wt");
    pedir_ecuaciones(m_coef);

    for(int i = 0; i < 5; i++)
        fprintf(archivo, "%d, %d, %d\n", m_coef[i][0], m_coef[i][1], m_coef[i][2]);

    fclose(archivo);

    return 0;
}

void pedir_nombre_archivo(char *nombre_archivo) {
    printf("Dame el nombre del archivo (sin extension): ");
    fgets(nombre_archivo, 193, stdin);
    quitar_enter(nombre_archivo);
    strcat(nombre_archivo, ".ecu");
}

void quitar_enter(char *nombre) {
    while (*++nombre != '\n');
    *nombre = '\0';
}

void pedir_ecuaciones(int m_coef[5][3]) {
    printf("Dame cinco ecuaciones de segundo grado.\n");
    printf("En cada renglon escribe los valores de los coeficientes de acuerdo al siguiente formato: ");
    printf("a, b, c\n");

    for (int i = 0; i < 5; i++)
        scanf("%d, %d, %d", &m_coef[i][0], &m_coef[i][1], &m_coef[i][2]);
}
