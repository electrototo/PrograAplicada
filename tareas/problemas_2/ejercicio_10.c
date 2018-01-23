/*
 *  autor: cristobal liendo i
 *  fecha: Sat 20 Jan 2018 02:25:52 PM CST
 *  descripcion: calcula los dias trascurridos de una fecha a otra
*/

#include <stdio.h>
#define LEAP(y) (y%4!=0)?0:(y%100!=0)?1:(y%400!=0)?0:1

int get_days(char *date_1, char *date_2, int (*days)[13]);
int verify(char *date, int *day, int *month, int *year, int (*days)[13]);

int main() {
    char date_1[11], date_2[11];
    int pass;

    int days[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };

    printf("Ingresa la primera fecha: ");
    scanf("%s", date_1);

    printf("Ingresa la segunda fecha: ");
    scanf("%s", date_2);

    pass = get_days(date_1, date_2, days);

    if (pass >= 0)
        printf("\nDias desde %s hasta %s: %d\n", date_1, date_2, pass);

    return 0;
}

int get_days(char *date_1, char *date_2, int (*days)[13]) {
    int dd1, mm1, aa1;
    int dd2, mm2, aa2;

    int total = 0;
    int curr = 0;

    if (!verify(date_1, &dd1, &mm1, &aa1, days))
        return -1;

    if (!verify(date_2, &dd2, &mm2, &aa2, days))
        return -1;

    if (aa1 > aa2 || (dd1 > dd2 && mm1 == mm2)) {
        printf("La segunda fecha debe ser mayor a la primera\n");

        return -1;
    }

    if (mm1 == mm2 && aa1 == aa2)
        total = dd2 - dd1;

    else {
        total += days[LEAP(aa1)][mm1] - dd1;

        while (++mm1 < mm2 || aa1 < aa2) {
            if (mm1 % 13 == 0) {
                mm1 = 1;
                aa1++;
            }

            total += days[LEAP(aa1)][mm1];
        }

        total += dd2;
    }

    return total;
}

int verify(char *date, int *day, int *month, int *year, int (*days)[13]) {
    char *nombres[] = {
        "",
        "enero",
        "febrero",
        "marzo",
        "abril",
        "mayo",
        "junio",
        "julio",
        "agosto",
        "septiembre",
        "octubre",
        "noviembre",
        "diciembre"
    };

    if (sscanf(date, "%d/%d/%d", day, month, year) != 3 ) {
        printf("\nEl formato de la fecha \"%s\" no coincide con el formato [aa/mm/aaaa]\n", date);

        return 0;
    }

    if (*month > 12 || *month < 1) {
        printf("\nEl mes es incorrecto\n");

        return 0;
    }

    if (*day < 1 || *day > days[LEAP(*year)][*month]) {
        printf("\n%s no tiene %d dias\n", nombres[*month], *day);

        return 0;
    }

    return 1;
}
