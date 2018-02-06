/*
 *  autor: cristobal liendo i
 *  fecha: Mon 05 Feb 2018 10:34:13 PM CST
 *  descripcion: decode script
*/

#include <stdio.h>
#include <string.h>
#include "image_func.h"

int main(int argc, char **argv) {
    IMAGE *image;
    FILE *to_hide;

    if (strcmp(argv[1], "-h") == 0) {
        printf("Usage:\n");
        printf("\t%s file_to_decode.raw\n", argv[0]);

        return 1;
    }

    image = load_image(argv[1]);
    printf("load image encoded.raw\n");

    FILE *decode;
    decode = fopen("decoded", "wb");

    int max_data = 0;
    int current = 0;
    for(int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            if ((y * (image->width) + x) % 8 == 0 && !(y == 0 && x == 0)) {
                fputc(current, decode);
                current = 0x00;
            }

            current <<= 1;
            current |= image->points[y][x] & 1;
        }
    }

    fclose(decode);
    close_image(&image);

    return 0;
}

