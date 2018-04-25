/*
 * autor: cristobal liendo i
 * fecha: Tue 24 Apr 2018 06:48:32 PM CDT
 * descripcion: 
*/

#include <stdio.h>

#define MAX 10

void print_tablero(int tablero[MAX][MAX]);
void check_winner(int tablero[MAX][MAX], int aux[MAX][MAX], int x, int y, int level, int dir);

int contador = 0;

int main() {
    int tablero[MAX][MAX];
    int aux[MAX][MAX];

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            tablero[i][j] = 0;
            aux[i][j] = 0;
        }
    }

    tablero[1][1] = 1;
    tablero[1][3] = 1;
    tablero[2][1] = 1;
    tablero[2][4] = 1;
    tablero[3][1] = 1;
    tablero[3][5] = 1;
    tablero[4][1] = 1;
    tablero[4][2] = 1;
    tablero[4][3] = 1;
    tablero[4][4] = 1;
    tablero[4][6] = 1;
    tablero[5][4] = 1;
    tablero[6][4] = 1;
    tablero[7][4] = 1;

    print_tablero(tablero);
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            check_winner(tablero, aux, j, i, 0, 0);

    printf("contador: %d\n", contador);

    return 0;
}

void print_tablero(int tablero[MAX][MAX]) {
    for (int y = 0; y < MAX; y++) {
        for (int x = 0; x < MAX; x++) {
            if (x % 9 == 0)
                printf("|");

            if (tablero[y][x] == 1)
                printf("O");
            else if (tablero[y][x] == -1)
                printf("X");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void check_winner_n(int tablero[MAX][MAX],int aux[MAX][MAX], int x, int y) {
  int tempx, tempy;
  tempx = x;
  tempy = y;

  while(aux[++tempx][y] && tablero[tempx][y]){
    aux[tempx][y] = 1;
    level++;
  }

  if(level == 3){
    contador++;
  }
  
}

/*
void check_winner(int tablero[MAX][MAX], int aux[MAX][MAX], int x, int y, int level, int dir) {
    printf("nivel: %d\n", level);
    printf("actual x, y: %d, %d\n", x, y);

    if (x >= MAX || x < 0 || y >= MAX || y < 0)
        return;

    if (tablero[y][x] != 1)
        return;

    if (level == 3) {
        printf("aumentando\n");
        contador++;
        return;
    }

    // visita el norte
    if (aux[y-1][x] != 1 && tablero[y-1][x] == 1) {
        aux[y-1][x] = 1;
        check_winner(tablero, aux, x, y - 1, level + 1);
    }

    // noreste
    if (aux[y - 1][x + 1] != 1 && tablero[y - 1][x + 1] == 1) {
        aux[y - 1][x + 1] = 1;
        check_winner(tablero, aux, x + 1, y - 1, level + 1);
    }

    // este
    if (aux[y][x + 1] != 1 && tablero[y][x + 1] == 1) {
        aux[y][x + 1] = 1;
        check_winner(tablero, aux, x + 1, y, level + 1);
    }

    // sureste
    if (aux[y + 1][x + 1] != 1 && tablero[y + 1][x + 1] == 1) {
        aux[y + 1][x + 1] = 1;
        check_winner(tablero, aux, x + 1, y + 1, level + 1);
    }

    // sur
    if (aux[y + 1][x] != 1 && tablero[y + 1][x] == 1) {
        aux[y + 1][x] = 1;
        check_winner(tablero, aux, x, y + 1, level + 1);
    }

    // suroeste
    if (aux[y + 1][x - 1] != 1 && tablero[y + 1][x - 1] == 1) {
        aux[y + 1][x - 1] = 1;
        check_winner(tablero, aux, x - 1, y + 1, level + 1);
    }

    // oeste
    if (aux[y][x - 1] != 1 && tablero[y][x - 1] == 1) {
        aux[y][x - 1] = 1;
        check_winner(tablero, aux, x - 1, y, level + 1);
    }

    // noroeste
    if (aux[y - 1][x - 1] != 1 && tablero[y - 1][x - 1] == 1) {
        aux[y - 1][x - 1] = 1;
        check_winner(tablero, aux, x - 1, y - 1, level + 1);
    }
}
*/
