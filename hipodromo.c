#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

void dibujarPista(int hipodromo[], int numCaballos, char* nombresCaballos[]) {
    int i, j;
    clear();
    for (i = 0; i < numCaballos; i++) {
        move(i+3, 0);
        printw("%s: ", nombresCaballos[i]);
        for (j = 1; j < hipodromo[i]; j++) {
            printw("-");
        }
    }
    refresh();
}

void Carrera(int hipodromo[], int numCaballos, int largoPista, char* nombresCaballos[]) {
    int a, i, j;
    srand(time(NULL));
    while (1) {
        usleep(50000);
        a = rand() % numCaballos;
        hipodromo[a]++;
        dibujarPista(hipodromo, numCaballos, nombresCaballos);
        if (hipodromo[a] == largoPista) {
        		clear();
            printw("\n\nEl ganador es: %s!\n", nombresCaballos[a]);
            refresh();
            break;
        }
        move(numCaballos+3, 0);
        for (i = 0; i < numCaballos; i++) {
            for (j = 0; j <= hipodromo[i]; j++) {
            }
            printw("  ");
        }
        refresh();
    }
}

int main() {
    int largoPista = 50;
    int numCaballos = 4;
    char *nombresCaballos[] = {"Estrella Nautica", "Princesa Alba", "Cristobal Colon", "El Pepe"};
    int hipodromo[numCaballos];
    int opcion, i;
    
    // INICIA EL MODO NCURSES.
    initscr();
    cbreak();
    noecho();
    clear();
    
    
    
    // SE GENERA EL MENÚ PARA APOSTAR RESPECTO A UN CABALLO.
      for (i = 0; i < numCaballos; i++) {
          hipodromo[i] = 0;
      }
    printw("----------------------------\n");
    printw("|   APUESTA DE CABALLOS    |\n");
    printw("----------------------------\n");
    move(2, 0);
    hline('-', 50);
    move(3, 0);
    for (i = 0; i < numCaballos; i++) {
        printw("    %d. %s\n", i+1, nombresCaballos[i]);
    }
    printw("    %d. Ninguno\n", numCaballos+1);
    move(numCaballos+4, 0);
    hline('-', 50);
    refresh();
    do { // INDICA QUE CABALLO 
        move(numCaballos+5, 0);
        printw("Indique por quien apuesta (1-%d): ", numCaballos+1);
        scanw("%d", &opcion);
    } while (opcion < 1 || opcion > numCaballos+1);
    if (opcion == numCaballos+1) {
        clear();
        dibujarPista(hipodromo, numCaballos, nombresCaballos);
        Carrera(hipodromo, numCaballos, largoPista, nombresCaballos);        
        printw("No ha apostado por ninguno.\n");
    }else {
        clear();
        dibujarPista(hipodromo, numCaballos, nombresCaballos);
        Carrera(hipodromo, numCaballos, largoPista, nombresCaballos);
    }
    getch();
    endwin();
    return 0;
}
