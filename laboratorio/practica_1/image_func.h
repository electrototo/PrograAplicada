
/*
 *  autor: cristobal liendo i
 *  fecha: Fri 26 Jan 2018 11:22:34 PM CST
 *  descripcion: header que contiene la definicion de las funciones para la
 *               libreria de manipulacion de imagenes
*/

#ifndef IMAGE_FUNC_H
#define IMAGE_FUNC_H

typedef struct IMAGE {
    int width;
    int height;
    int max_value;

    char format[3];

    unsigned char **points;
} IMAGE;

IMAGE *create_canvas(int width, int height);
IMAGE *load_image(char *path);
void close_image(IMAGE **image);
FILE *write_image(IMAGE *image, char *path);
void inverse_image(IMAGE *image);
void equalize_hist(IMAGE *image);
void scale_image_nearest(IMAGE **image, int width, int height);
void scale_image_linear(IMAGE **image, int width, int height);

#endif
