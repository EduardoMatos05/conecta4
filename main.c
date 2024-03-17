#include <stdio.h>
#include <stdlib.h>
#define NUM_COLUMNAS 7
#define NUM_FILAS 6

void imprimirTablero(int matriz[][NUM_COLUMNAS]);
int encontrarEspacioVacioInferior(int matriz[][NUM_COLUMNAS], int opcionColumna);
void ponerPieza(int matriz[][NUM_COLUMNAS], int fila, int columna, int pieza);
int chequeoGanador(int matriz[][NUM_COLUMNAS],int fila,int columna,int pieza);
int jugarTurno(int jugador);

int tablero[NUM_FILAS][NUM_COLUMNAS] = {0};

int main(int argc, char *argv[]) {
    int juego, turno, opcion, filaDeFicha;
    juego = 1;
    turno = 1;

    while (juego)
    {
        imprimirTablero(tablero);
        if (turno % 2 == 1) 
            juego = jugarTurno(1);
        else 
            juego = jugarTurno(2);
        turno++;

    }
    imprimirTablero(tablero);


    return 0;
}

void imprimirTablero(int matriz[][NUM_COLUMNAS]) {
    int ii, jj;
    for(jj=0;jj<NUM_COLUMNAS;jj++){
        printf(" %i  ", jj);
    }
    printf("\n");
    for (ii = 0; ii < NUM_FILAS; ii++) {
        printf("|");
        for (jj = 0; jj < NUM_COLUMNAS; jj++) {
            //imprimir ficha roja
            if (matriz[ii][jj] == 1)
            {
                printf("\033[0;31m"); 
                printf("O "); 
                printf("\033[0m");
                printf("| ");  
            }
            //imprimir ficha azul
            else if (matriz[ii][jj] == 2)
            {
                printf("\033[0;36m"); 
                printf("O "); 
                printf("\033[0m"); 
                printf("| "); 
            }
            else 
                printf("%i | ", matriz[ii][jj]);
            
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
    printf("columna llena\n");
    return -1;
}


void ponerPieza(int matriz[][NUM_COLUMNAS], int fila, int columna, int pieza){
    matriz[fila][columna]= pieza;
    return;
}

int chequeoGanador(int matriz[][NUM_COLUMNAS],int fila,int columna,int pieza){
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


int jugarTurno(int jugador){

    int opcion, filaDeFicha;
    printf("Turno jugador %i ", jugador);

    //obtener y validar input
    do { 
        do {
            printf("Ingrese una columna de (0 a 6)\n");
            scanf("%i", &opcion);
        } while ((opcion < 0) || (opcion > 6));

        filaDeFicha= encontrarEspacioVacioInferior(tablero, opcion);
    } while (filaDeFicha == -1);

    ponerPieza(tablero, filaDeFicha, opcion, jugador);
    if(chequeoGanador(tablero, filaDeFicha, opcion, jugador)){
        printf("gano el jugador %i\n", jugador);
        return 0;
    }
    
    return 1;

}
