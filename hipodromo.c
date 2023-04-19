#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

// Función para dibujar la pista de carrera
void dibujarPista(int hipodromo[], int numCaballos, char *nombresCaballos[]) {
    int i, j;
    clear();
    // Imprime la lista de caballos con su nombre y su posición en la pista
    for (i = 0; i < numCaballos; i++) {
        movimiento(i+2, 0);
        printw("%s: ", nombresCaballos[i]);
        for (j = 1; j < hipodromo[i]; j++) {
            printw("-");
        }
    }
    refresh();
}

// Función que simula la carrera de caballos
void Carrera(int hipodromo[], int numCaballos, int largoPista, char *nombresCaballos[]) {
    int a, i, j;
    // Inicializa el generador de números aleatorios
    srand(time(NULL));
    // El bucle se ejecuta hasta que un caballo llega a la meta
    while (1) {
        usleep(50000); // Pequeña pausa para hacer la carrera más realista
        a = rand() % numCaballos; // Selecciona un caballo al azar para avanzar
        hipodromo[a]++; // Avanza al caballo seleccionado
        dibujarPista(hipodromo, numCaballos, nombresCaballos); // Dibuja la pista de carrera actualizada
        if (hipodromo[a] == largoPista) { // Si el caballo seleccionado llega a la meta
            // Muestra al caballo ganador en la última posición de la pantalla
            movimiento(numCaballos+3, 0);
            printw("\nCaballo ganador: %s\n", nombresCaballos[a]);
            refresh();
            break; // Sale del bucle
        }
    }
}

int main() {
    int largoPista = 50;
    int numCaballos = 4;
    char *nombresCaballos[] = {"Estrella Nautica", "Princesa Alba", "Cristobal Colon", "El Pepe"};
    int hipodromo[numCaballos];
    int i, opcion;

    // Inicia el modo ncurses
    initscr();
    cbreak();
    noecho();
    clear();

    // Inicializa el arreglo de posiciones de los caballos en la pista
    for (i = 0; i < numCaballos; i++) {
        hipodromo[i] = 0;
    }

    // Muestra el título de la carrera y el menú para seleccionar un caballo
    movimiento(0, 0);
    printw("Carrera de caballos");
    movimiento(1, 0);
    printw("-------------------");
    movimiento(2, 0);
    printw("Seleccione un caballo:");
    movimiento(3, 0);
    printw("----------------------");
    for (i = 0; i < numCaballos; i++) {
        movimiento(i+4, 0);
        printw("%d. %s", i+1, nombresCaballos[i]);
    }
    movimiento(numCaballos+4, 0);
    printw("5. Ninguno");
    return 0;
}