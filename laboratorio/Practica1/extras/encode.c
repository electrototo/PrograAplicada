/*
 *  autor: cristobal liendo i
 *  fecha: Mon 05 Feb 2018 10:30:33 PM CST
 *  descripcion: cifrar archivos en imagenes PGM
*/

#include <stdio.h>
#include <string.h>
#include "image_func.h"

unsigned char reverse(unsigned char letter) {
    unsigned char new = 0;

    for (int i = 0; i < 8; i++, letter >>= 1) {
        new <<= 1;
        new |= letter & 1;
    }

    return new;
}

int main(int argc, char **argv) {
    IMAGE *image;
    FILE *to_hide;

    unsigned char current = 0;
    unsigned char on = 0xFF;
    unsigned char off = 0xFE;

    unsigned long max_data, current_size;
    int index = 0;

    if (strcmp(argv[1], "-h") == 0) {
        printf("Usage:\n");
        printf("\t%s input_image.pgm file_to_encode.*\n", argv[0]);

        return 0;
    }

    image = load_image(argv[1]);
    to_hide = fopen(argv[2], "rb");

    fseek(to_hide, 0, SEEK_END);

    max_data = (image->width * image->height) / 8;
    current_size = ftell(to_hide);

    printf("max data that can be encoded:    %lu bytes\n", max_data);
    printf("size of file:                    %lu bytes\n", current_size);

    fseek(to_hide, 0, SEEK_SET);

    for (int y = 0; y < image->height; y++) {
        for(int x = 0; x < image->width; x++) {
            if ((y * (image->width) + x) % 8 == 0)
                current = reverse(fgetc(to_hide));

            if (current & 0x1)
                image->points[y][x] = (image->points[y][x] | 1) & on;
            else 
                image->points[y][x] = (image->points[y][x] | 1) & off;

            current >>= 1;
        }
    }

    write_image(image, "encoded.raw");
    close_image(&image);
    fclose(to_hide);

    return 0;
}

