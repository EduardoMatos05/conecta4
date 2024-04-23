#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
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

    printf("utiliza las flechas para mover la ficha y enter para dejarla caer\n");
    system("pause");

    while (juego)
    {
        //imprimirTablero(tablero);
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

    printf("\033[0m"); 

    printf("\n");
    for (ii = 0; ii < NUM_FILAS; ii++) {
        printf("| ");
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
            //imprimir el 0
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
    //printf("columna llena\n");
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

    int opcion, filaDeFicha, columnaSelec;
    char c;
    c = ' ';
    columnaSelec = 0;

    
    //ciclo do por si la columna esta llena
    do {
        //ciclo while para checar si ya se ingreso enter
        while ((int)c != 13 )
        {
            system("cls");

            if (jugador == 1)
                printf("\033[0;31m"); 
            else 
                printf("\033[0;36m");
            

            printf("Turno jugador %i \n", jugador);

            //imprimir las ficha que se esta por tirar en el lugar adeacuado
            for (int i = 0; i < NUM_COLUMNAS; i++)
                if (i == columnaSelec)
                    printf("  O  ");
                else 
                    printf("    ");

            imprimirTablero(tablero);

            
            c = getch();

            //checa si c es alguna de las flechas y se se puede recorrer la ficha, en dado caso la recorre
            if ((int)c == 77 && columnaSelec < NUM_COLUMNAS - 1)
            {
                columnaSelec++;
            }

            else if ((int)c == 75 && columnaSelec > 0)
            {
                columnaSelec--;
            }
            
        }

        //encuentra el espacio correspondiente a la ficha que se dejo caer 
        opcion = columnaSelec;
        filaDeFicha= encontrarEspacioVacioInferior(tablero, opcion);
        //si no hay espacio la funcion regresa -1, ponemos que c = ' ' para poder volver a ingresar al ciclo while
        if (filaDeFicha == -1)
            c = ' ';
    } while (filaDeFicha == -1);

    ponerPieza(tablero, filaDeFicha, opcion, jugador);

    //detecta ganaddor
    if(chequeoGanador(tablero, filaDeFicha, opcion, jugador))
    {
        system("cls");
        //checa para imprimir el texto del color correspondiente
        if (jugador == 1)
                printf("\033[0;31m"); 
            else 
                printf("\033[0;36m");
    
        printf("gano el jugador %i\n", jugador);
        return 0;
    }
    
    return 1;

}
