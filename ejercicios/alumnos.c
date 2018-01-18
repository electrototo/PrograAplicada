/*
 * autor: cristobal liendo i
 * fecha: 16/1/18
 * descripcion: lee datos de alumnos y muestra un menu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu_principal();
void preguntar_datos(int a_index, char **nombres, float (*calificaciones)[3]);
void quitar_enter(char *);
void guardar_en_archivo(char **nombres, float (*calificaciones)[3]);
void leer_datos_archivo(char **nombres, float (*calificaciones)[3]);
void mostrar_datos_alumno(char **nombres, float (*calificaciones)[3]);
void promedios_alumnos(char **nombres, float (*calificaciones)[3]);
FILE *get_file(char *mode);

int main() {
    int choice, data_in = 0;

    char *nombres[10];
    float calificaciones[10][3];

    while ((choice = menu_principal()) != 6) {
        switch (choice) {
            case 1:
                for (int i = 0; i < 10; i++)
                    preguntar_datos(i, nombres, calificaciones);

                data_in = 1;

                break;

            case 2:
                if (data_in)
                    guardar_en_archivo(nombres, calificaciones);

                else {
                    printf("No hay informacion en memoria\n");
                    printf("\nPresiona cualquier tecla para continuar...");
                    getchar();
                }


                break;

            case 3:
                leer_datos_archivo(nombres, calificaciones);
                data_in = 1;

                break;

            case 4:
                if (data_in)
                    mostrar_datos_alumno(nombres, calificaciones);

                else {
                    printf("No hay informacion en memoria\n");
                    printf("\nPresiona cualquier tecla para continuar...");
                    getchar();
                }

                break;

            case 5:
                if (data_in)
                    promedios_alumnos(nombres, calificaciones);

                else {
                    printf("No hay informacion en memoria\n");
                    printf("\nPresiona cualquier tecla para continuar...");
                    getchar();
                }

                break;

            default:
                break;
        }
    }

    if (data_in)
        for (int i = 0; i < 10; i++)
            free(nombres[i]);

    return 0;
}

int menu_principal() {
    system("clear");

    int choice;

    printf("Que deseas hacer?\n");
    printf("[1] Leer datos de alumnos\n");
    printf("[2] Guardar en archivo\n");
    printf("[3] Leer datos de archivo\n");
    printf("[4] Mostrar datos de alumnos\n");
    printf("[5] Calcular y mostrar promedios por alumnos\n");
    printf("[6] Salir\n");

    do {
        printf("Opcion: ");
        scanf("%d", &choice);
        getchar();
    } while (choice < 1 || choice > 6);

    system("clear");

    return choice;
}

void quitar_enter(char *name) {
    while (*++name != '\n');

    *name = '\0';
}

void preguntar_datos(int a_index, char **nombres, float (*calificaciones)[3]) {
    char tmp[200];

    printf("\nIngresa el nombre del alumno: ");
    fgets(tmp, 199, stdin);
    quitar_enter(tmp);

    nombres[a_index] = strdup(tmp);

    for (int i = 0; i < 3; i++) {
        printf("\tIngresa la calificacion #%d: ", i + 1);
        scanf("%f", &calificaciones[a_index][i]);
        getchar();
    }
}

FILE *get_file(char *mode) {
    FILE *file;
    char fname[100];

    printf("\tIngresa el nombre del archivo: ");
    scanf("%s", fname);
    getchar();

    file = fopen(fname, mode);

    if (file == NULL)
        printf("\tEl archivo especificado no existe\n");

    return file;
}

void guardar_en_archivo(char **nombres, float (*calificaciones)[3]) {
    FILE *file = get_file("w");

    for (int i = 0; i < 10; i++) {
        fprintf(file, "%s\n", nombres[i]);
        fprintf(file, "%f\n", calificaciones[i][0]);
        fprintf(file, "%f\n", calificaciones[i][1]);
        fprintf(file, "%f\n", calificaciones[i][2]);
    }

    printf("\tSe guardaron exitosamente las calificaciones de los alumnos\n");

    printf("Presione enter para continuar...");
    getchar();

    fclose(file);
}

void imprimir_dato_alumno(int a_index, char **nombres, float (*calificaciones)[3]) {
    printf("\tNombre del alumno: %s\n", nombres[a_index]);
    printf("\t  Calificacion #1: %.2f\n", calificaciones[a_index][0]);
    printf("\t  Calificacion #2: %.2f\n", calificaciones[a_index][1]);
    printf("\t  Calificacion #3: %.2f\n\n", calificaciones[a_index][2]);
}

void leer_datos_archivo(char **nombres, float (*calificaciones)[3]) {
    FILE *file = get_file("r");
    char temp[200];

    for (int i = 0; i < 10; i++) {
        fscanf(file, "%s\n", temp);
        fscanf(file, "%f\n", &calificaciones[i][0]);
        fscanf(file, "%f\n", &calificaciones[i][1]);
        fscanf(file, "%f\n", &calificaciones[i][2]);

        nombres[i] = strdup(temp);
        memset(temp, 0, 200);

        imprimir_dato_alumno(i, nombres, calificaciones);
    }

    printf("Presione enter para continuar...");
    getchar();

    fclose(file);
}

void mostrar_datos_alumno(char **nombres, float (*calificaciones)[3]) {
    for (int i = 0; i < 10; i++)
        imprimir_dato_alumno(i, nombres, calificaciones);

    printf("Presione enter para continuar...");
    getchar();
}

void promedios_alumnos(char **nombres, float (*calificaciones)[3]) {
    float avg = 0;

    for (int i = 0; i < 10; i++) {
        for(int j = 0; j < 3; j++)
            avg += calificaciones[i][j] / 3;

        printf("\tAlumno %s:\n", nombres[i]);
        printf("\t  Promedio %.2f\n\n", avg);

        avg = 0;
    }

    printf("Presione enter para continuar...");
    getchar();
}
