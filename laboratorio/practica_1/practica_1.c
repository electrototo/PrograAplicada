/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 01:45:49 PM CST
 *  descripcion: manipulacion de una imagen en PGM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// aqui se incluyen todas las definiciones de las funciones
#include "image_func.h"

// son todos los menus que se le van a presentar al usuario
int main_menu();
void load_image_menu(char *filename);
void resize_menu(int *width, int *height);
void cont();
void error();
void splash_screen();

int main(int argc, char **argv) {
    IMAGE *to_edit, *process;
    int choice, set = 0, saved = 0;
    int width, height;
    char filename[100];

    splash_screen();

    // repite mientras que el usuario no haya decidido salirse
    while((choice = main_menu()) != 6) {
        // el usuario decidio cargar en memoria la imagen
        if (choice == 1) {
            load_image_menu(filename);
            to_edit = load_image(filename);

            if (to_edit != NULL)
                set = 1;
        }
        else if (set){
            switch(choice) {
                // obten el inverso
                case 2:
                    inverse_image(to_edit);
                    printf("Inverso exitosamente obtenido\n");
                    cont();

                    break;

                // ecualiza la imagen
                case 3:
                    equalize_hist(to_edit);
                    printf("Imagen exitosamente ecualizada\n");
                    cont();

                    break;

                // cambia de tamano
                case 4:
                    resize_menu(&width, &height);
                    scale_image_nearest(&to_edit, width, height);
                    printf("Nuevas dimensiones de la imagen: %d, %d\n", width, height);
                    cont();

                    break;

                // guarda la imagen
                case 5:
                    printf("Ingresa el nombre de como se deberia guardar: ");
                    scanf("%s", filename);
                    getchar();

                    write_image(to_edit, filename);
                    saved = 1;

                    break;
            }
        }
        // si el usuario decide modificar la imagen, sin previamente haberla abierto
        // marca error
        else
            error();
    }

    // guarda una copia de la imagen si el usuario no cambio los cambios
    if (set && !saved) {
        printf("Cambios no guardados. Guardando la imagen como copia.raw\n");
        write_image(to_edit, "copia.raw");
    }

    // libera la memoria de la imagen
    if (set)
        close_image(&to_edit);

    return 0;
}

// seccion de menus
void splash_screen() {
    system("clear");
    printf("Programa disenado y elaborado por Cristobal Liendo I.\n");
    cont();
    system("clear");
    printf("Este programa se encarga de hacer manipulaciones basicas con imagenes de formato PGM\n");
    printf("Las manipulaciones que se pueden realizar son las siguientes:\n");
    printf("    1. Obtener la inversa de la imagen\n");
    printf("    2. Ecualizar el histograma\n");
    printf("    3. Cambiar de tamano\n");
    printf("\nPara poder utilizar cualquier funcion previamente mencionada, es necesario tener\n");
    printf("guardada en la computadura una imagen en formato PGM, posteriormente se debe cargar\n");
    printf("en memoria la imagen. Si la imagen no esta cargada en memoria, no se podra realizar\n");
    printf("ninguna manipulacion. Si no se guardan los cambios al salir, se crea una restauracion\n");
    printf("con nombre \"copia.raw\"\n");
    cont();
}

int main_menu() {
    system("clear");

    int choice;

    printf("Menu principal\n");
    printf("  [1] Cargar en memoria la imagen\n");
    printf("  [2] Inverso de la imagen\n");
    printf("  [3] Ecualizar histograma\n");
    printf("  [4] Cambiar de tamano\n");
    printf("  [5] Guardar imagen\n");
    printf("  [6] Salir\n");

    do {
        printf("Opcion: ");
        scanf("%d", &choice);
        getchar();
    } while (choice < 1 || choice > 8);

    system("clear");

    return choice;
}

void load_image_menu(char *filename) {
    printf("Ingresa el nombre de la imagen: ");
    scanf("%s", filename);
    getchar();
}

void resize_menu(int *width, int *height) {
    printf("Ingresa el nuevo tamano horizontal: ");
    scanf("%d", width);
    getchar();
    printf("Ingresa el nuevo tamano vertical: ");
    scanf("%d", height);
    getchar();
}

void cont() {
    printf("\nPresiona enter para continuar...");
    getchar();
}

void error() {
    printf("Necesitas cargar primero una imagen\n");
    cont();
}
