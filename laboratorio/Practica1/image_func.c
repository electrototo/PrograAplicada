/*
 *  autor: cristobal liendo i
 *  fecha: Fri 26 Jan 2018 11:22:34 PM CST
 *  descripcion: libreria que contiene el codigo para la manipulacion de imagenes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image_func.h"

// genera un "canvas" blanco de dimesiones width * height
// regresa una estructura tipo IMAGEN
IMAGE *create_canvas(int width, int height) {
    IMAGE *new_image = (IMAGE *) malloc(sizeof(IMAGE));

    // aloca espacio para las hileras de la imagen
    new_image->points = (unsigned char **) malloc(sizeof(unsigned char **) * height);

    // limpia toda la basura del arreglo
    memset(new_image->points, 0, sizeof(unsigned char **) * height);

    // aloca espacio para las columnas de cada hilera
    for (int y = 0; y < height; y++) {
        new_image->points[y] = (unsigned char *) malloc(sizeof(unsigned char *) * width);
        memset(new_image->points[y], 0, sizeof(unsigned char ) * width);
    }

    new_image->width = width;
    new_image->height = height;

    return new_image;
}

// crea una estructura de tipo IMAGEN con los datos necesarios para futuras
// manioulaciones: tamano en x, tamano en y, y los pixeles de la imagen
IMAGE *load_image(char *path) {
    FILE *image_file;
    IMAGE *new_image = (IMAGE *) malloc(sizeof(IMAGE));

    image_file = fopen(path, "r");

    // checa la existencia del archivo
    if (image_file == NULL) {
        printf("No existe el archivo %s\n", path);

        return NULL;
    }

    fread(new_image->format, 2, 1, image_file);

    // obtiene los tamanos de la imagen y los guarda en la nueva estructura
    fscanf(image_file, "%d %d %d", &new_image->width, &new_image->height,
           &new_image->max_value);

    fseek(image_file, 1, SEEK_CUR);

    // aloca espacio para las hileras de la imagen
    new_image->points = (unsigned char **) malloc(sizeof(unsigned char **) * new_image->height);

    // aloca espacio para las columnas de cada hilera de la imagen
    for (int y = 0; y < new_image->height; y++)
        new_image->points[y] = (unsigned char *) malloc(sizeof(unsigned char *) * new_image->width);

    // obtiene byte por byte los pixeles de la imagen
    // cada pixel = 1 byte
    for (int y = 0; y < new_image->height; y++) {
        for (int x = 0; x < new_image->width; x++) {
            fread(&new_image->points[y][x], 1, 1, image_file);
        }
    }

    fclose(image_file);

    return new_image;
}

// libera toda la memoria previamente alocada para la estructura y
// pixeles de la imagen
void close_image(IMAGE **image) {
    // recorre cada hilera de la estructura y libera las columnas
    for (int y = 0; y < (*image)->height; y++)
        free((*image)->points[y]);

    // libera las hileras
    free((*image)->points);

    // libera la estructura
    free(*image);

    *image = NULL;
}

// escribe en un archivo los pixeles de la imagen *image y guarda el archivo
// con el nombre especificado en *path
FILE *write_image(IMAGE *image, char *path) {
    FILE *image_file;
    char header[100];

    image_file = fopen(path, "wb");

    if (image_file == NULL) {
        printf("No se pudo escribir en el archivo");

        return NULL;
    }

    // guarda el encabezado de la imagen
    sprintf(header, "%s %d %d %d ", image->format, image->width, image->height,
            image->max_value);

    fwrite(header, strlen(header), 1, image_file);

    // guarda cada pixel de la imagen en un archivo
    for (int y = 0; y < image->height; y++)
        for (int x = 0; x < image->width; x++)
            fputc(image->points[y][x], image_file);

    fclose(image_file);
}

// obten la inversa de la imagen con el complemento a 2
void inverse_image(IMAGE *image) {
    for (int y = 0; y < image->height; y++)
        for (int x = 0; x < image->width; x++)
            image->points[y][x] = ~(image->points[y][x]);
}

// genera la ecualizacion del histograma
void equalize_hist(IMAGE *image) {
    // genera un arreglo de frecuencias de intensidad de pixeles
    unsigned long *frequencies = (unsigned long *) calloc(image->max_value + 1,
        sizeof(unsigned long));

    int pixels = image->width * image->height;
    int pos = 0;

    // recorre todos los pixeles de la imagen para generar la tabla de frecuencias
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            pos = image->points[y][x];
            frequencies[pos]++;
        }
    }

    // genera la tabla de frecuencias acumuladas
    for (int i = 1; i < image->max_value + 1; i++)
        frequencies[i] += frequencies[i - 1];

    // a todos los pixeles de la imagen, aplica la formula de la referencia no. 1
    // del documento IEEE
    for(int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            // pos es la intensidad del pixel en la posicion y, x
            pos = image->points[y][x];
            image->points[y][x] = image->max_value * ((float) frequencies[pos] / (float) pixels);
        }
    }

    free(frequencies);
}

// genera la imagen con las nuevas dimensiones
void scale_image_nearest(IMAGE **image, int width, int height) {
    IMAGE *new_image = create_canvas(width, height);

    float x_ratio, y_ratio;
    int x, y;

    new_image->max_value = (*image)->max_value;
    strcpy(new_image->format, (*image)->format);

    // calcula las razones de los nuevos tamanos
    x_ratio = ((*image)->width) / (double) width;
    y_ratio = ((*image)->height) / (double) height;

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            // x y y son la posicion en la imagen original
            x = column * x_ratio;
            y = row * y_ratio;

            new_image->points[row][column] = (*image)->points[y][x];
        }
    }

    close_image(image);

    *image = new_image;
}

// cambia de tamano la imagen usando interpolacion bilinear
void scale_image_linear(IMAGE **image, int width, int height) {
    IMAGE *new_image = create_canvas(width, height);

    float x_ratio, y_ratio, new_ratio_x, new_ratio_y;
    float x_diff, y_diff;

    int x, y;

    unsigned char A, B, C, D;
    unsigned char new_data_1, new_data_2, new_data_3;

    new_image->max_value = (*image)->max_value;
    strcpy(new_image->format, (*image)->format);

    new_ratio_y = ((*image)->width - 1) / (double) width;
    new_ratio_x = ((*image)->height - 1) / (double) height;

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            x = new_ratio_x * column;
            y = new_ratio_y * row;

            x_diff = (new_ratio_x * (double) column) - x;
            y_diff = (new_ratio_y * (double) row) - y;

            A = (*image)->points[y][x];
            B = (*image)->points[y][x + 1];
            C = (*image)->points[y + 1][x];
            D = (*image)->points[y + 1][x + 1];

            new_data_1 = A * (1 - x_diff) * (1 - y_diff) + B * (x_diff) * (1 - y_diff) +
                         C * (y_diff) * (1 - x_diff) + D * (x_diff * y_diff);

            new_image->points[row][column] = new_data_1;
        }
    }

    close_image(image);

    *image = new_image;
}
