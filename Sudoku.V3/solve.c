//
//      solve.c
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "testJeu.h"
#include "afficheGrille.h"
#include "lireFichier.h"

int nbSolveInvocations = 0;
int nbSolutions = 0;
clock_t clockTime;
int lastLigne=8;
int lastColonne=8;
char **grilleResultat;

//--------------------------------------------------------
//
//          C A L C U L
//
//--------------------------------------------------------
int calcul(char **grille, int lig, int col){
    //printf("===============================================================\n");
    //printf("solve => debut recherche de solution de la grille en %d,%d\n", lig, col);
    //afficheGrille(grille);
    //getchar();
    nbSolveInvocations++;
    if (nbSolveInvocations > 1000000) return 0;     // trop d'iterations sans resultats, on annule la recherche
    for (int ligne = 0 ; ligne < 9 ; ligne ++){
        for (int colonne = 0 ; colonne < 9 ; colonne ++){
            if (grille[ligne][colonne] == ' '){
                // cette case est a trouver 
                for (int val = '1' ; val <= '9' ; val++){
                    //printf("solve => test de %c en %d,%d\n", val, lig, col);
                    if (testJeu(grille,ligne+1, colonne+1, val, 1) == 1){
                        grille[ligne][colonne] = val;
                        if (calcul(grille, ligne, colonne) == 0){
                            //printf("solve => %c NOK en %d,%d\n", val, ligne, colonne);
                            grille[ligne][colonne] = grilleInitiale[ligne*9+colonne];
                        } else {
                            //printf("solve => %c OK en %d,%d\n", val, ligne, colonne);
                            if ((ligne == lastLigne) && (colonne == lastColonne)) {
                                //printf(".");
                                nbSolutions ++;
                            }
                            // on sauvegarde cette grille comme resultat
                            for (int i = 0 ; i < 9 ; i++){
                                for (int j = 0 ; j < 9 ; j++){
                                    grilleResultat[i][j]= grille[i][j];
                                }
                            }
                        }
                    }
                }
                //printf("solve => NOK : on arrive a la fin de la ligne %d \n", lig);
                grille[ligne][colonne] = grilleInitiale[ligne*9+colonne];
                return 0;
            }
        }
    }
    //printf("solve => fin \n");
    return 1;
}

//--------------------------------------------------------
//
//          I N I T S O L V E
//
//--------------------------------------------------------
void initSolve(void){
    nbSolveInvocations = 0;
    nbSolutions = 0;
    int index = 81;
    char car;

    while ((car = grilleInitiale[--index]) != ' '){
        //printf("solve(init) => test de la case %d(%c) \n", index, car);
        lastColonne--;
        if (lastColonne < 0){
            lastColonne = 8;
            lastLigne--;
        }
    }
    //printf("Solve(init) => derniere case libre %d,%d (%c)\n", lastLigne, lastColonne, car);
}

//--------------------------------------------------------
//
//          B I L A N S O L V E
//
//--------------------------------------------------------
void bilanSolve(void){
    printf("Bilan recherche de solutions \n");
    printf("  nombre d'invocations       = %d\n", nbSolveInvocations);
    printf("  nombre solutions trouvees  = %d\n", nbSolutions);
    printf("  temps de resolution (ms)   = %f\n", (float)clockTime/CLOCKS_PER_SEC*1000);
}

//--------------------------------------------------------
//
//          S O L V E
//
//--------------------------------------------------------
int solve(char **grille, int modeSilence){
    clockTime = clock();

    // allocation de la memoire pour la grille de jeu
    grilleResultat = malloc(9 * sizeof(char*));
    for (int i = 0 ; i < 9 ; i++){
        grilleResultat[i]=malloc(9 * sizeof(char));
        for (int j = 0 ; j < 9 ; j++){
            grilleResultat[i][j] = ' ';
        }
    }
    initSolve();
    calcul(grille, 0, 0);
    printf("\n");
    clockTime = clock() - clockTime;
    if (modeSilence == 0){
        bilanSolve();
    }
    // restauration de la grille resultat dans la grille
    for (int i = 0 ; i < 9 ; i++){
        for (int j = 0 ; j < 9 ; j++){
            grille[i][j]= grilleResultat[i][j];
        }
    }  
    // liberation de la mémoire allouée
    for (int i = 0 ; i < 9 ; i++){
        free(grilleResultat[i]);
    }
    free(grilleResultat);
    return nbSolutions;
}
