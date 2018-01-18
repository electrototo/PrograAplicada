/*
 * autor: cristobal liendo i
 * fecha: 16/1/18
 * descripcion: lee datos de alumnos y muestra un menu
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct alumno {
    char nombre[100];
    float calificaciones[3];
} alumno_t;

int menu_principal();
void preguntar_datos(alumno_t *);
void quitar_enter(char *);
void guardar_en_archivo(alumno_t *);
void leer_datos_archivo(alumno_t *);
void mostrar_datos_alumno(alumno_t *);
void promedios_alumnos(alumno_t *);
FILE *get_file(char *mode);

int main() {
    int choice;
    alumno_t alumnos[10];

    while ((choice = menu_principal()) != 6) {
        switch (choice) {
            case 1:
                for (int i = 0; i < 10; i++)
                    preguntar_datos(&alumnos[i]);

                break;

            case 2:
                guardar_en_archivo(alumnos);
                break;

            case 3:
                leer_datos_archivo(alumnos);
                break;

            case 4:
                mostrar_datos_alumno(alumnos);
                break;

            case 5:
                promedios_alumnos(alumnos);
                break;

            default:
                break;
        }
    }

    return 0;
}

int menu_principal() {
    system("clear");

    int choice;

    printf("\nQue deseas hacer?\n");
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

void preguntar_datos(alumno_t *alumno) {
    printf("\nIngresa el nombre del alumno: ");
    fgets(alumno->nombre, 199, stdin);
    quitar_enter(alumno->nombre);

    for (int i = 0; i < 3; i++) {
        printf("\tIngresa la calificacion #%d: ", i + 1);
        scanf("%f", &alumno->calificaciones[i]);
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

void guardar_en_archivo(alumno_t *alumnos) {
    FILE *file = get_file("w");

    for (int i = 0; i < 10; i++) {
        fprintf(file, "%s\n", alumnos[i].nombre);
        fprintf(file, "%f\n", alumnos[i].calificaciones[0]);
        fprintf(file, "%f\n", alumnos[i].calificaciones[1]);
        fprintf(file, "%f\n", alumnos[i].calificaciones[2]);
    }

    printf("\tSe guardaron exitosamente las calificaciones de los alumnos\n");

    printf("Presione enter para continuar...");
    getchar();

    fclose(file);
}

void imprimir_dato_alumno(alumno_t *alumno) {
    printf("\tNombre del alumno: %s\n", alumno->nombre);
    printf("\t  Calificacion #1: %.2f\n", alumno->calificaciones[0]);
    printf("\t  Calificacion #2: %.2f\n", alumno->calificaciones[1]);
    printf("\t  Calificacion #3: %.2f\n\n", alumno->calificaciones[2]);
}

void leer_datos_archivo(alumno_t *alumnos) {
    FILE *file = get_file("r");

    for (int i = 0; i < 10; i++) {
        fscanf(file, "%s\n", alumnos[i].nombre);
        fscanf(file, "%f\n", &alumnos[i].calificaciones[0]);
        fscanf(file, "%f\n", &alumnos[i].calificaciones[1]);
        fscanf(file, "%f\n", &alumnos[i].calificaciones[2]);

        imprimir_dato_alumno(&alumnos[i]);
    }

    printf("Presione enter para continuar...");
    getchar();

    fclose(file);
}

void mostrar_datos_alumno(alumno_t * alumnos) {
    for (int i = 0; i < 10; i++)
        imprimir_dato_alumno(&alumnos[i]);

    printf("Presione enter para continuar...");
    getchar();
}

void promedios_alumnos(alumno_t *alumnos) {
    float avg = 0;

    for (int i = 0; i < 10; i++) {
        for(int j = 0; j < 3; j++)
            avg += alumnos[i].calificaciones[j] / 3;

        printf("\tAlumno %s:\n", alumnos[i].nombre);
        printf("\t  Promedio %.2f\n\n", avg);

        avg = 0;
    }

    printf("Presione enter para continuar...");
    getchar();
}
