/*
 *  autor: cristobal liendo i
 *  fecha: Fri 19 Jan 2018 01:45:49 PM CST
 *  descripcion: manipulacion de una imagen en PGM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IMAGE {
    int width;
    int height;
    int max_value;

    char format[3];

    unsigned char **points;
} IMAGE;

IMAGE *create_canvas(int width, int height) {
    IMAGE *new_image = (IMAGE *) malloc(sizeof(IMAGE));

    new_image->points = (unsigned char **) malloc(sizeof(unsigned char **) * height);

    // TODO: use calloc
    memset(new_image->points, 0, sizeof(unsigned char **) * height);

    for (int y = 0; y < height; y++) {
        new_image->points[y] = (unsigned char *) malloc(sizeof(unsigned char *) * width);
        memset(new_image->points[y], 0, sizeof(unsigned char ) * width);
    }

    new_image->width = width;
    new_image->height = height;

    return new_image;
}

IMAGE *load_image(char *path) {
    FILE *image_file;
    IMAGE *new_image = (IMAGE *) malloc(sizeof(IMAGE));

    image_file = fopen(path, "r");

    if (image_file == NULL) {
        printf("No existe el archivo %s\n", path);

        return NULL;
    }

    fread(new_image->format, 2, 1, image_file);

    fscanf(image_file, "%d %d %d", &new_image->width, &new_image->height,
           &new_image->max_value);

    fseek(image_file, 1, SEEK_CUR);

    new_image->points = (unsigned char **) malloc(sizeof(unsigned char **) * new_image->height);

    for (int y = 0; y < new_image->height; y++)
        new_image->points[y] = (unsigned char *) malloc(sizeof(unsigned char *) * new_image->width);

    for (int y = 0; y < new_image->height; y++) {
        for (int x = 0; x < new_image->width; x++) {
            fread(&new_image->points[y][x], 1, 1, image_file);
        }
    }

    fclose(image_file);

    return new_image;
}

void close_image(IMAGE **image) {
    for (int y = 0; y < (*image)->height; y++)
        free((*image)->points[y]);

    free((*image)->points);
    free(*image);

    *image = NULL;
}

FILE *write_image(IMAGE *image, char *path) {
    FILE *image_file;
    char header[100];

    image_file = fopen(path, "wb");

    if (image_file == NULL) {
        printf("No se pudo escribir en el archivo");

        return NULL;
    }

    sprintf(header, "%s %d %d %d ", image->format, image->width, image->height,
            image->max_value);

    fwrite(header, strlen(header), 1, image_file);

    printf("write_image\n");

    for (int y = 0; y < image->height; y++)
        for (int x = 0; x < image->width; x++)
            fputc(image->points[y][x], image_file);

    fclose(image_file);
}

void inverse_image(IMAGE *image) {
    for (int y = 0; y < image->height; y++)
        for (int x = 0; x < image->width; x++)
            image->points[y][x] = ~(image->points[y][x]);
}

void equalize_hist(IMAGE *image) {
    unsigned long *frequencies = (unsigned long *) calloc(image->max_value + 1,
        sizeof(unsigned long));

    int pixels = image->width * image->height;
    int pos = 0;

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            pos = image->points[y][x];
            frequencies[pos]++;
        }
    }

    for (int i = 1; i < image->max_value + 1; i++)
        frequencies[i] += frequencies[i - 1];

    for(int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            pos = image->points[y][x];
            image->points[y][x] = image->max_value * ((float) frequencies[pos] / (float) pixels);
        }
    }

    free(frequencies);
}

void scale_image_linear(IMAGE **image, int width, int height) {
    IMAGE *new_image = create_canvas(width, height);

    float x_ratio, y_ratio;
    int x, y;

    new_image->max_value = (*image)->max_value;
    strcpy(new_image->format, (*image)->format);

    x_ratio = ((*image)->width) / (double) width;
    y_ratio = ((*image)->height) / (double) height;

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            x = column * x_ratio;
            y = row * y_ratio;

            new_image->points[row][column] = (*image)->points[y][x];
        }
    }

    close_image(image);

    *image = new_image;
}

int main(int argc, char **argv) {
    IMAGE *process;

    process = load_image(argv[1]);
    scale_image_linear(&process, 640, 480);

    equalize_hist(process);
    write_image(process, argv[2]);
    close_image(&process);

    return 0;
}
