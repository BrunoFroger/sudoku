//
//      efface.c
//

#include <stdio.h>

#include "lireFichier.h"


//--------------------------------------------------------
//
//          E F F A C E
//
//--------------------------------------------------------
void efface(char **grille, int ligne, int colonne){
    char carInitial;
    ligne = ligne - 1;
    colonne = colonne - 1;
    //printf("efface => on efface la cellule %d,%d\n",ligne, colonne);
    carInitial = grilleInitiale[ligne*9+colonne];
    //printf("efface => on cherche a effacer le caractère %c en %d,%d\n", carInitial, ligne, colonne);
    if (grilleInitiale[ligne*9+colonne] == ' '){
        grille[ligne][colonne] = ' ';
    } else {
        printf("ERREUR : Impossible effacer une case initiale\n");
    }
}
