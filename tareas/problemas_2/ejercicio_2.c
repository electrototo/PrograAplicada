/*
 * autor: cristobal liendo
 * fecha: 19/01/17
 * descripcion: pregunta cuantas temperaturas, pide temperaturas e imprime
 *              las temperaturas que son mayor o igual a la media
*/

#include <stdio.h>
#include <stdlib.h>

int get_num_temps();

int main() {
    int n_temps, above = 0;
    float *temps, *temps_init, avg;

    printf("Cuantas temperaturas deseas ingresar (5 - 100)? ");
    n_temps = get_num_temps();

    temps_init = (float *) malloc(sizeof(float) * n_temps);
    temps = temps_init;
    
    for (int i = 0; i < n_temps; i++, temps++) {
        printf("\tTemperatura #%d: ", i + 1);
        scanf("%f", temps);

        avg += *temps / n_temps; 
    }

    printf("\nPromedio: %.2f\n", avg);
    printf("Temperaturas mayores o igual al promedio:\n");

    for (int i = 0; i < n_temps; i++)
        if (temps_init[i] >= avg) {
            printf("\tTemperatura: %.2f\n", temps_init[i]);
            above++;
        }

    printf("\nTotal de temperaturas mayores al promedio: %d\n", above);

    free(temps_init);

    return 0;
}

int get_num_temps() {
    int n, pass = 1;

    do {
        if (!pass) {
            printf("\nLa cantidad ingresada no entra dentro del rango 5 - 100\n");
            printf("Intenta de nuevo: ");
            pass = 1;
        }

        scanf("%d", &n);
        getchar();

        if (n < 5 || n > 100)
            pass = 0;

    } while(!pass);

    return n;
}
