/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 01:45:49 PM CST
 *  descripcion: manipulacion de una imagen en PGM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image_func.h"

int main(int argc, char **argv) {
    IMAGE *process;

    process = load_image(argv[1]);

    scale_image_linear(&process, process->width * 2, process->height * 2);
    equalize_hist(process);

    write_image(process, argv[2]);
    close_image(&process);

    return 0;
}
