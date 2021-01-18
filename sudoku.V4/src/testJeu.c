//
//      testJeu.c
//

#include <stdio.h>

#include "../inc/grille.h"

//--------------------------------------------------------
//
//          T E S T J E U
//
//--------------------------------------------------------
int testJeu(char **grille, int ligne, int colonne, char valeur, int silence){
    if (silence == 0) printf("\n\n---------------------------------------------------\n");
    printf("TestJeu => verification de la valeur %c en %d,%d\n", valeur, ligne, colonne);
    //getchar();

    // test si on essaie de modifier une valeur de la grille d'origine
    if (grilleInitiale[ligne*9+colonne] != ' '){
        if (silence == 0) printf("ERREUR : impossible de modifier une valeur initiale %d,%d(%c)\n", ligne, colonne, valeur);
        return 0;
    } else {
        printf("TestJeu => on ne modifie pas une valeur initiale\n");
    }

    // test si ligne entre 0 et 8
    if ((ligne < 0) || (ligne > 8)){
        if (silence == 0) printf("ERREUR : ligne (%d) n'est pas entre 1 et 9\n", ligne);
        return 0;
    } else {
        printf("TestJeu => numero de ligne valide\n");
    }

    // test si colonne entre 0 et 8
    if ((colonne < 0) || (colonne > 8)){
        if (silence == 0) printf("ERREUR : colonne (%d) n'est pas entre 1 et 9\n", colonne);
        return 0;
    } else {
        printf("TestJeu => numero de colonne valide\n");
    }

    // test si valeur entre 1 et 9
    if ((valeur < '1') || (valeur > '9')){
        if (silence == 0) printf("ERREUR : valeur (%c) n'est pas entre 1 et 9\n", valeur);
        return 0;
    } else {
        printf("TestJeu => numero de valeur valide\n");
    }

    // test si la saisie se fait dans une case vide
    if (grille[ligne][colonne] != ' '){
        if (silence == 0) printf("ERREUR : case %d,%d deja occupee par le chiffre %c\n", ligne+1, colonne+1, grille[ligne][colonne]);
        return 0;
    } else {
        printf("TestJeu => saisie dans une case vide valide\n");
    }

    // test si la valeur saisie n'est pas deja dans la ligne
    // TODO la nouvelle valeur n'est pas dans la ligne avant de faire ce test
    // il faut l'ajouter en testant que c'est possible et prevoir retour arriere
    if (grilleTestLigneValide(grille, ligne) != 0){
        if (silence == 0) printf("ERREUR : cette valeur (%c en %d,%d) est deja dans la ligne \n", valeur, ligne, colonne);
        return 0;
    } else {
        printf("TestJeu => toutes les valeur de la ligne sont valide\n");
    }

    // test si la valeur saisie n'est pas deja dans la colonne
    if (grilleTestColonneValide(grille, colonne) != 0){
        if (silence == 0) printf("ERREUR : cette valeur est deja dans la colonne\n");
        return 0;
    } else {
        printf("TestJeu => toutes les valeur de la colonne sont valide\n");
    }

    // test si la valeur dans la region
    int indexLigneCarre = ligne / 3;
    int indexColonneCarre = colonne / 3;
    //printf("Analyse du carre en pos %d, %d\n", indexLigneCarre, indexColonneCarre);
    if (grilleTestRegionValide(grille,indexLigneCarre,indexColonneCarre) != 0){
        if (silence == 0) printf("region %d,%d invalide\n",indexLigneCarre, indexColonneCarre);
        return 0;
    } else {
        printf("TestJeu => toutes les valeur de la region sont valide\n");
    }
    /*
    int DebutLigne = indexLigneCarre * 3;
    int finLigne = DebutLigne + 3;
    int Debutcolonne = indexColonneCarre * 3;
    int finColonne = Debutcolonne + 3;
    for (int lig = DebutLigne ; lig < finLigne ; lig++){
        for (int col = Debutcolonne ; col < finColonne ; col ++){
            printf("test de la case %d,%d(%c) avec %c\n", lig, col, grille[lig][col], valeur);
            if (grille[lig][col] == valeur){
                if (silence == 0) printf("ERREUR : la valeur %c est deja dans le carre\n", valeur);
                return 0;
            }
        }
    }
    */

    // tous les tests sont valides, on peut repondre qu'il n'y a pas d'erreur
    if (silence == 0) printf("testJeu => val %c en %d,%d OK\n",valeur,ligne,colonne);
    return 1;
}
