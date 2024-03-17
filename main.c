#include <stdio.h>
#include <stdlib.h>
#define NUM_COLUMNAS 7
#define NUM_FILAS 6

void imprimirTablero(int matriz[][NUM_COLUMNAS]);

int main(int argc, char *argv[]) {
    int tablero[NUM_FILAS][NUM_COLUMNAS] = {0};
    int juego, turno, opcion;
    juego = 1;
    turno = 1;

    while (juego)
    {
        imprimirTablero(tablero);
        if (turno % 2 == 1) {
            printf("Turno jugador 1\n");
            scanf("%i", &opcion);
        } else {
            printf("Turno jugador 2\n");
            scanf("%i", &opcion);
        }

        turno++;
    }

    return 0;
}

void imprimirTablero(int matriz[][NUM_COLUMNAS]) {
    int ii, jj;
    for(jj=0;jj<NUM_COLUMNAS;jj++){
        printf(" %i", jj);
    }
    printf("\n");
    for (ii = 0; ii < NUM_FILAS; ii++) {
        printf("|");
        for (jj = 0; jj < NUM_COLUMNAS; jj++) {
            printf("%i|", matriz[ii][jj]);
        }
        printf("\n");
    }
}
