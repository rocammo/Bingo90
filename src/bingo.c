/**
 * Autor: Rodrigo Casamayor <alu.89657@usj.es>
 * Fecha: 19 de Abril de 2018.
 *
 * Programa: Juego del bingo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define FILA 3
#define COLUMNA 9

typedef struct carton { int casilla[FILA][COLUMNA]; int id; } Carton;
typedef struct bingo {
    Carton *carton; // cartones en juego
    int   cantidad; // numero cartones

    Carton *cartonL; // cartones con linea
    int numLineas;   // numero lineas cantadas
    Carton *cartonB; // cartones con bingo
    int numBingos;   // numero bingos cantados
} Bingo;
typedef struct partida { int *numeros; } Partida; // Guarda los numeros que apa-
                                                  // recen durante la partida

void BINGO (void);
void nuevaPartida    (Bingo *bingo, Partida *partida);
void generarCartones (Bingo *bingo);
void mostrarCartones (Bingo bingo,  Partida partida,  Carton *carton, int bombo, int num);
void estadoJuego     (Bingo *bingo, Partida *partida, int modoJuego);
int  main (void) { BINGO(); return(0); } // FUNCION MAIN()

void BINGO (void)
{
    char jugando = 'S';
    while (jugando == 'S' || jugando == 's')
    {
        srand(time(NULL)); // semilla aleatoriedad

        Bingo bingo;
        Partida partida;
        nuevaPartida(&bingo, &partida);


        // Regenerar?
        do
        {
            printf("%cDesea volver a jugar? <S/n>: ", 168);
            scanf(" %c", &jugando);
        } while ((jugando != 'S' && jugando != 's') &&
                 (jugando != 'n' && jugando != 'N'));
        if (jugando == 'S' || jugando == 's') system("cls");
    }
}

/*
 * @function nuevaPartida
 * ----------------------
 * @param bingo    (estructura bingo)
 * @param partida  (estructura partida)
 */
void nuevaPartida    (Bingo *bingo, Partida *partida)
{
    int i; // iterador

    /* Cabecera */
    printf("%c", 218); for (i = 0; i < 61; i++) { printf("%c", 196); } printf("%c\n",   191);
    printf("%c                    == JUEGO DEL BINGO ==                    %c\n",  179, 179);
    printf("%c  (Autor:  Rodrigo Casamayor Moragriega <alu.89657@usj.es>)  %c\n",  179, 179);
    printf("%c", 192); for (i = 0; i < 61; i++) { printf("%c", 196); } printf("%c\n\n", 217);

    /* Comprueba si es la primera partida y muestra un mensaje de bienvenida u otro */
    static int nPartida = 1;
    if (nPartida == 1) {
        printf("Bienvenido/a a Bingo!\n");
        for (i = 0; i < 21; i++) { printf("%c", 196); } printf("\n");
    } else {
        printf("Bienvenido/a de nuevo a Bingo!\n");
        for (i = 0; i < 30; i++) { printf("%c", 196); } printf("\n");
    } nPartida++;

    /* Escoge el modo de juego */
    int modoJuego;
    do {
        printf("Seleccione el modo de juego:\n");
        printf("  [1] Paso a paso.\n"
               "  [2] Juego completo.\n");
        printf("> ");
        scanf("%d", &modoJuego);
    } while (modoJuego != 1 && modoJuego != 2);

    /* Solicita al usuario el numero de cartones a jugar */
    printf("\nIndique el n%cmero de cartones a jugar: ", 163);
    scanf("%d", &(bingo->cantidad)); printf("\n");

    /* Prepara los cartones */
    generarCartones(bingo);

    /* Desarrollo del juego */
    estadoJuego(bingo, partida, modoJuego);
}
/*
 * @function generarCartones
 * -------------------------
 * @param bingo  (estructura bingo)
 */
void generarCartones (Bingo *bingo)
{
    int i, j, n; // iteradores

    /* Prepara tantos cartones como el usuario haya solicitado */
    bingo->carton = (Carton *) malloc(bingo->cantidad * sizeof(Carton));

    /* Construye los cartones */
    for (n = 0; n < bingo->cantidad; n++) {
        /* Rellena las casillas */
        for (j = 0; j < 9; j++)
        {
            do {
                for (i = 0; i < 3; i++)
                {
                    bingo->carton[n].casilla[i][j] = rand() % (9 + 1 - 0) + 0;
                    switch (j)
                    {
                        case 1:
                            bingo->carton[n].casilla[i][j] += 10;
                            break;
                        case 2:
                            bingo->carton[n].casilla[i][j] += 20;
                            break;
                        case 3:
                            bingo->carton[n].casilla[i][j] += 30;
                            break;
                        case 4:
                            bingo->carton[n].casilla[i][j] += 40;
                            break;
                        case 5:
                            bingo->carton[n].casilla[i][j] += 50;
                            break;
                        case 6:
                            bingo->carton[n].casilla[i][j] += 60;
                            break;
                        case 7:
                            bingo->carton[n].casilla[i][j] += 70;
                            break;
                        case 8:
                            bingo->carton[n].casilla[i][j] += (80 + 1);
                            break;
                    }
                }
            } while(bingo->carton[n].casilla[0][j] == bingo->carton[n].casilla[1][j] ||
                    bingo->carton[n].casilla[1][j] == bingo->carton[n].casilla[2][j] ||
                    bingo->carton[n].casilla[0][j] == bingo->carton[n].casilla[2][j] ||
                    bingo->carton[n].casilla[0][j]  > bingo->carton[n].casilla[1][j] ||
                    bingo->carton[n].casilla[1][j]  > bingo->carton[n].casilla[2][j]);
        }

        /* Crea huecos */
        int huecos, pos;
        for (i = 0; i < 3; i++) {
            huecos = 0, pos = 0;
            while (huecos < 4) {
                pos = rand() % (8 + 1 - 0) + 0;                   // Genera posicion aleatoria
                if (bingo->carton[n].casilla[i][pos] != -1) {     // Verifica si no se ha generado antes
                    bingo->carton[n].casilla[i][pos] = -1;        // Guarda la posicion en la casilla
                    huecos++;
                }
            }
        }

        /* Asigna un identificador (id) a cada carton */
        bingo->carton[n].id = n;
    }
}

/*
 * @function mostrarCartones
 * ---------------------
 * @param  bingo    (estructura bingo)
 * @param  partida  (estructura partida)
 * @param  carton   (estructura carton)
 * @param  bombo    cantidad de bolas salidas del bombo
 * @param  num      cantidad de cartones
 */
void mostrarCartones (Bingo bingo,  Partida partida,  Carton *carton, int bombo, int num)
{
    HANDLE cmd = GetStdHandle(STD_OUTPUT_HANDLE); // salida consola
    int i, j, k, n = 0; // iteradores

    while (n < num) {
        printf("\nCart%cn n. %d\n", 162, carton[n].id + 1);
        for (i = 0; i < FILA; i++) {
            if (i == 0) {
                for (j = 0; j < COLUMNA; j++) {
                    if (j == 0) printf("%c%c%c%c%c%c", 201, 205, 205, 205, 205, 203);
                    else if  (j == (COLUMNA - 1)) printf("%c%c%c%c%c", 205, 205, 205, 205, 187);
                    else printf("%c%c%c%c%c", 205, 205, 205, 205, 203);
                }
            }
            printf("\n");
            for (j = 0; j < COLUMNA; j++) {
                if (carton[n].casilla[i][j] == -1) {
                    if (j == 0) printf("%c %c%c %c", 186, 219, 219, 186);
                    else printf(" %c%c %c", 219, 219, 186);
                } else {
                    if (j == 0) printf("%c", 186);
                    printf(" ");
                    /* Marca la casilla correspondiente al numero que haya salido, */
                    /* en caso de haber coincidencia */
                    for (k = 0; k < bombo; k++) {
                        if (carton[n].casilla[i][j] == partida.numeros[k])
                            SetConsoleTextAttribute(cmd, 164);
                    }
                    if (j == 0) printf("%2d", carton[n].casilla[i][j]);
                    else printf("%2d", carton[n].casilla[i][j]);
                    SetConsoleTextAttribute(cmd, 7);
                    printf(" %c", 186);
                }
            }
            printf("\n");
            if (i == (FILA - 1)) {
                for (j = 0; j < COLUMNA; j++) {
                    if (j == 0) printf("%c%c%c%c%c%c", 200, 205, 205, 205, 205, 202);
                    else if  (j == (COLUMNA - 1)) printf("%c%c%c%c%c", 205, 205, 205, 205, 188);
                    else printf("%c%c%c%c%c", 205, 205, 205, 205, 202);
                }
            } else {
                for (j = 0; j < COLUMNA; j++) {
                    if (j == 0) printf("%c%c%c%c%c%c", 204, 205, 205, 205, 205, 206);
                    else if  (j == (COLUMNA - 1)) printf("%c%c%c%c%c", 205, 205, 205, 205, 185);
                    else printf("%c%c%c%c%c", 205, 205, 205, 205, 206);
                }
            }
        }
        printf("\n");
        n++;
    }
}

/*
 * @function estadoJuego
 * ---------------------
 * @param  bingo      (estructura bingo)
 * @param  partida    (estructura partida)
 * @param  modoJuego  modo de juego: paso a paso / juego completo
 */
void estadoJuego     (Bingo *bingo, Partida *partida, int modoJuego)
{
    int i, j, k, n, x, y; // iteradores
    int bool_L, bool_B;
    int contador1 = 0, contador2 = 0; // contadores auxiliares

    /* Inicializa todo a 0 */
    int bombo = 0; // contador numeros bombo
    int bola = 0;
    int cartones_linea = 0, cartones_bingo = 0;
    bingo->numLineas = 0;
    bingo->numBingos = 0;

    /* Asigna memoria dinamica */
    partida->numeros =  (int *) malloc(sizeof(int));
    bingo->cartonL = (Carton *) malloc((bingo->cantidad * 3) * sizeof(Carton));
    bingo->cartonB = (Carton *) malloc((bingo->cantidad * 3) * sizeof(Carton));

    while (bingo->numBingos == 0) {
        /* Reasigna memoria dinamica */
        partida->numeros = (int *) realloc(partida->numeros, (bombo + 1) * sizeof(int));

        /* Extrae una bola al azar del bombo (sin repeticion) */
        bola = rand() % (90 + 1 - 0) + 0;
        if (bombo != 0) {
            for (k = 0; k < bombo; k++) {
                if (bola == partida->numeros[k]) {
                    bola = rand() % (90 + 1 - 0) + 0;
                    k = 0;
                }
            }
        }
        partida->numeros[bombo] = bola;

        /* Comprueba si se ha producido alguna linea o bingo */
        bingo->numLineas = 0; bingo->numBingos = 0;
          cartones_linea = 0;   cartones_bingo = 0;
        for (n = 0; n < bingo->cantidad; n++) {
            contador2 = 0;
            bool_L = 0; bool_B = 0;
            for (i = 0; i < 3; i++) {
                contador1 = 0;
                for (j = 0; j < 9; j++) {
                    for (k = 0; k < (bombo + 1); k++) {
                        if ((bingo->carton[n].casilla[i][j] != -1) &&
                            (bingo->carton[n].casilla[i][j] == partida->numeros[k]))
                            contador1++;
                    }
                }
                // linea: todas las casillas marcadas de una misma fila (5)
                if (contador1 == 5) {
                    bingo->numLineas++;
                    for (x = 0; x < FILA; x++) { for (y = 0; y < COLUMNA; y++) {
                        bingo->cartonL[cartones_linea].casilla[x][y] = bingo->carton[n].casilla[x][y];
                    } } bingo->cartonL[cartones_linea].id = bingo->carton[n].id;

                    if (bool_L == 0) {
                        cartones_linea++;
                    } bool_L = 1;
                }

                // bingo: todas las casillas marcadas de un mismo carton (15) <-> 3 lineas
                contador2 += contador1;
                if (contador2 == (5 * 3)) {
                    bingo->numBingos++;
                    for (x = 0; x < FILA; x++) { for (y = 0; y < COLUMNA; y++) {
                        bingo->cartonB[cartones_bingo].casilla[x][y] = bingo->carton[n].casilla[x][y];
                    } } bingo->cartonB[cartones_bingo].id = bingo->carton[n].id;

                    if (bool_B == 0) {
                        cartones_bingo++;
                    } bool_B = 1;
                }
            }
        }

        if (modoJuego == 1 || (modoJuego == 2 && bingo->numBingos != 0)) {
            /* Muestra todos los cartones */
            printf("(%d) No. %d\n", (bombo + 1), partida->numeros[bombo]);
            for (i = 0; i < 16; i++) { printf("%c", 196); }
            mostrarCartones(*bingo, *partida, bingo->carton, (bombo + 1), bingo->cantidad);

            /* Muestra los cartones con linea y bingo */
            if (cartones_linea > 0) {
                printf("\n"); for (k = 0; k < 19; k++) { printf("%c", 196); }
                printf("%cLINEA%c", 180, 195);
                for (k = 0; k < 20; k++) { printf("%c", 196); }

                mostrarCartones(*bingo, *partida, bingo->cartonL, (bombo + 1), cartones_linea);
            }
            if (cartones_bingo > 0) {
                printf("\n"); for (k = 0; k < 19; k++) { printf("%c", 196); }
                printf("%cBINGO%c", 180, 195);
                for (k = 0; k < 20; k++) { printf("%c", 196); }

                mostrarCartones(*bingo, *partida, bingo->cartonB, (bombo + 1), cartones_bingo);
            }

            /* Muestra el resumen de lineas y bingos */
            printf("%c", 218); for (i = 0; i < 44; i++) { printf("%c", 196); } printf("%c\n",     191);
            printf("%cNo. lineas: %2d "
                   "                "
                   "No. bingos: %d%c\n", 179, bingo->numLineas, bingo->numBingos, 179);
            printf("%c", 192); for (i = 0; i < 44; i++) { printf("%c", 196); } printf("%c\n",     217);

            /* Muestra las bolas que han salido */
            printf(" Bolas:");
            for (i = 0, j = 0; i < (bombo + 1); i++, j++) {
                if (j == 16) { printf("\n"); j = -1; }
                printf(" (%d)", partida->numeros[i]);
            }
            printf("\n\n");

            /* Espera la intervencion del usuario para continuar */
            system("pause"); printf("\n\n");
        }
        bombo++;
    }
    /* Libera memoria dinamica */
    free(bingo->cartonL);
    free(bingo->cartonB);
    free(partida->numeros);
    free(bingo->carton);
}
