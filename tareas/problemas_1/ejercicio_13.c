/*
 * autor: cristobal liendo
 * fecha: 17/1/18
 * descripcion: se ingresan 10 numeros, se imprime la suma de los numeros pares,
 *              se indica cuantos numeros pares existen, se muestra la media aritmetica
 *              de los impares e indica la cantidad de numeros impares que fueron
 *              ingresados
*/

#include <stdio.h>

int main() {
    int odd, even, sum_even, actual;
    float avg_odd;

    odd = even = avg_odd = sum_even = 0;

    printf("A continuacion ingresa 10 numeros:\n");

    for (int i = 0; i < 10; i++) {
        printf("Ingresa el numero #%d: ", i + 1);
        scanf("%d", &actual);

        if (actual % 2 == 0) {
            even++;
            sum_even += actual;
        }
        else {
            odd++;
            avg_odd += actual;
        }
    }

    if (odd != 0)
        avg_odd /= odd;

    printf("\nCantidad de numeros pares:                 %d\n", even);
    printf("Suma de los numeros pares:                 %d\n\n", sum_even);
    printf("Cantidad de numeros impares:               %d\n", odd);
    printf("Media aritmetica de los numeros impares:   %.2f\n", avg_odd);


    return 0;
}
