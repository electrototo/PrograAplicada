/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 01:45:49 PM CST
 *  descripcion: manipulacion de una imagen en PGM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image_func.h"

int main_menu() {
    int choice;
    
    printf("Menu principal\n");
    printf("  [1] Cargar en memoria la imagen\n");
    printf("  [2] Inverso de la imagen\n");
    printf("  [3] Ecualizar histograma\n");
    printf("  [4] Cambiar de tamano\n");
    printf("  [5] Ocultar archivo\n");
    printf("  [6] Decodificar archivo\n");
    printf("  [7] Guardar imagen\n");
    printf("  [8] Salir\n");

    do {
        printf("Opcion: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 7);

    return choice;
}

void load_image_menu(char *filename) {
    printf("Ingresa el nombre de la imagen: ");
    scanf("%s", filename);
}

void resize_menu(int *width, int *height) {
    printf("Ingresa el nuevo tamano horizontal: ");
    scanf("%d", width);
    printf("Ingresa el nuevo tamano vertical: ");
    scanf("%d", height);
}

int main(int argc, char **argv) {
    IMAGE *process;

    process = load_image(argv[1]);

    // scale_image_linear(&process, process->width * 2, process->height * 2);
    // equalize_hist(process);
    inverse_image(process);

    write_image(process, argv[2]);
    close_image(&process);

    return 0;
}
