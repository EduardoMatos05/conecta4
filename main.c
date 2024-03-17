#include <stdio.h>
#include <stdlib.h>
#define NUM_COLUMNAS 7
#define NUM_FILAS 6

void imprimirTablero(int matriz[][NUM_COLUMNAS]);
int encontrarEspacioVacioInferior(int matriz[][NUM_COLUMNAS], int opcionColumna);
void ponerPieza(int matriz[][NUM_COLUMNAS], int fila, int columna, int pieza);
int chequeoHorizontalVertical(int matriz[][NUM_COLUMNAS],int fila,int columna,int pieza);

int main(int argc, char *argv[]) {
    int tablero[NUM_FILAS][NUM_COLUMNAS] = {0};
    int juego, turno, opcion, filaDeFicha;
    juego = 1;
    turno = 1;

    while (juego)
    {
        imprimirTablero(tablero);
        if (turno % 2 == 1) {
            printf("Turno jugador 1\n");
            scanf("%i", &opcion);
            filaDeFicha= encontrarEspacioVacioInferior(tablero, opcion);
            ponerPieza(tablero, filaDeFicha, opcion, 1);
            if(chequeoHorizontalVertical(tablero, filaDeFicha, opcion, 1)){
                printf("gano el jugador 1\n");
                juego = 0;
            }
        } else {
            printf("Turno jugador 2\n");
            scanf("%i", &opcion);
            filaDeFicha= encontrarEspacioVacioInferior(tablero, opcion);
            ponerPieza(tablero, filaDeFicha, opcion, 2);
            if(chequeoHorizontalVertical(tablero, filaDeFicha, opcion, 2)){
                printf("gano el jugador 2\n");
                juego = 0;
            }
        }

        turno++;
    }
    imprimirTablero(tablero);

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

int encontrarEspacioVacioInferior(int matriz[][NUM_COLUMNAS], int opcionColumna) {
    int fila;
    for (fila = NUM_FILAS - 1; fila >= 0; fila--) {
        if (matriz[fila][opcionColumna] == 0) {
            return fila;
        }
    }
    return -1;
}


void ponerPieza(int matriz[][NUM_COLUMNAS], int fila, int columna, int pieza){
    matriz[fila][columna]= pieza;
    return;
}

int chequeoHorizontalVertical(int matriz[][NUM_COLUMNAS],int fila,int columna,int pieza){
    int ii, jj;

    for(ii=0; ii<=NUM_COLUMNAS-4; ii++){
        if(matriz[fila][ii]== pieza && matriz[fila][ii+1]== pieza && matriz[fila][ii+2]==pieza && matriz[fila][ii+3]== pieza){
            return 1;//verdadero
        }
    }

    for(ii=0; ii<=NUM_FILAS-4; ii++){
        if(matriz[ii][columna]== pieza && matriz[ii+1][columna]== pieza && matriz[ii+2][columna]== pieza && matriz[ii+3][columna]== pieza){
            return 1; // verdadero
        }
    }

//chequeo diagonal: /

    //encontrar el caso base a checar, en diagonal hacia abajo sin que se salga del tablero
    ii = fila;
    jj = columna;
    while ((ii < NUM_FILAS - 1) &&  (jj > 0 ))
    {
        ii++;
        jj--;
    }

    //checa para todos los casos yendo en diagonal hacia arriba sin que se salga
    for(ii=ii ,jj = jj ; (ii -3 >= 0) && (jj<=NUM_COLUMNAS-4); ii--, jj++){
        if(matriz[ii][jj]== pieza && matriz[ii-1][jj+1]== pieza && matriz[ii-2][jj+2]== pieza && matriz[ii-3][jj+3]== pieza){
            return 1; // verdadero
        }
    }

//chequeo diagonal: "\"

    //encontrar el caso base a checar, en diagonal hacia abajo sin que se salga del tablero
    ii = fila;
    jj = columna;
    while ((ii < NUM_FILAS - 1) &&  (jj < NUM_COLUMNAS -1 ))
    {
        ii++;
        jj++;
    }

    //checa para todos los casos yendo en diagonal hacia arriba sin que se salga
    for(ii=ii ,jj = jj ; (ii - 3 >= 0) && (jj - 3 >= 0); ii--, jj--){
        if(matriz[ii][jj]== pieza && matriz[ii-1][jj-1]== pieza && matriz[ii-2][jj-2]== pieza && matriz[ii-3][jj-3]== pieza){
            return 1; // verdadero
        }
    }
    return 0;//falso
}