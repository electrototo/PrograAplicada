/*
 * autor: cristobal liendo
 * fecha: 17/01/18
 * descripcion: suma un dia a la fecha introducida, tomando en cuenta
 *              anos biciestos.
*/

#include <stdio.h>
#define LEAP(y) (y%4!=0)?0:(y%100!=0)?1:(y%400!=0)?0:1

int main() {
    int days[2][13] = {
        {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {-1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };

    // dd mm aaaa
    int day, month, year;

    printf("Ingresa la fecha en formato dd/mm/aaaa: ");
    scanf("%d/%d/%d", &day, &month, &year);

    day = ++day % (days[LEAP(year)][month] + 1);

    if (day == 0) {
        day++;

        month = ((++month) % 13 == 0) ? ++year, 1: month;
    }

    printf("\nUn dia despues: %02d/%02d/%4d\n", day, month, year);

    return 0;
}
