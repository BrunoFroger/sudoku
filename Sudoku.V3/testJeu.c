//
//      testJeu.c
//

#include <stdio.h>

#include "lireFichier.h"

//--------------------------------------------------------
//
//          T E S T J E U
//
//--------------------------------------------------------
int testJeu(char **grille, int ligne, int colonne, char valeur, int silence){
    //if (silence == 0) printf("\n\n---------------------------------------------------\n");
    //printf("TestJeu => verification de la valeur %c en %d,%d\n", valeur, ligne, colonne);
    //getchar();
    ligne = ligne - 1;
    colonne = colonne - 1;

    // test si on essaie de modifier une valeur de la grille d'origine
    if (grilleInitiale[ligne*9+colonne] != ' '){
        if (silence == 0) printf("ERREUR : impossible de modifier une valeur initiale\n");
        return 0;
    }
    // test si les valeurs saisies sont entre 1 et 9
    if ((ligne < 0) || (ligne > 9) ||(colonne < 0) || (colonne > 9) ||(valeur < '0') || (valeur > '9')){
        if (silence == 0) printf("ERREUR : une des valeur n'est pas entre 1 et 9\n");
        return 0;
    }

    // test si la saisie se fait dans une case vide
    if (grille[ligne][colonne] != ' '){
        if (silence == 0) printf("ERREUR : case %d,%d deja occupee par le chiffre %c\n", ligne+1, colonne+1, grille[ligne][colonne]);
        return 0;
    }

    // test si la valeur saisie n'est pas deja dans la ligne
    for (int col = 0 ; col < 9 ; col++){
        if (grille[ligne][col] == valeur){
            if (silence == 0) printf("ERREUR : cette valeur est deja dans la ligne\n");
            return 0;
        }
    }

    // test si la valeur saisie n'est pas deja dans la colonne
    for (int lig = 0 ; lig < 9 ; lig++){
        //printf("test %d,%d (%c) avec valeur %c\n", lig, colonne+1, grille[lig][colonne], valeur);
        if (grille[lig][colonne] == valeur){
            if (silence == 0) printf("ERREUR : cette valeur est deja dans la colonne\n");
            return 0;
        }
    }

    // test si la valeur dans le carre
    int indexLigneCarre = ligne / 3;
    int indexColonneCarre = colonne / 3;
    //printf("Analyse du carre en pos %d, %d\n", indexLigneCarre, indexColonneCarre);
    int DebutLigne = indexLigneCarre * 3;
    int finLigne = DebutLigne + 3;
    int Debutcolonne = indexColonneCarre * 3;
    int finColonne = Debutcolonne + 3;
    for (int lig = DebutLigne ; lig < finLigne ; lig++){
        for (int col = Debutcolonne ; col < finColonne ; col ++){
            //printf("test de la case %d,%d(%c) avec %c\n", lig, col, grille[lig][col], valeur);
            if (grille[lig][col] == valeur){
                if (silence == 0) printf("ERREUR : la valeur %c est deja dans le carre\n", valeur);
                return 0;
            }
        }
    }


    // tous les tests sont valides, on peut repondre qu'il n'y a pas d'erreur
    //if (silence == 0) printf("testJeu => val %c en %d,%d OK\n",valeur,ligne,colonne);
    return 1;
}
