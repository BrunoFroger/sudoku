//
//      solve.c
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "../inc/testJeu.h"
#include "../inc/afficheGrille.h"
#include "../inc/grille.h"

int nbSolveInvocations = 0;
int nbSolutions = 0;
clock_t clockTime;
char **grilleResultat;

//--------------------------------------------------------
//
//          C A L C U L S O L V E
//
//--------------------------------------------------------
int calculSolve(char **grille, int lig, int col){
    //printf("===============================================================\n");
    //printf("solve => debut recherche de solution de la grille en %d,%d\n", lig, col);
    afficheGrille(grille);
    getchar();
    nbSolveInvocations++;
    if (nbSolveInvocations > 1000000) { // trop d'iterations sans resultats, on annule la recherche
        printf("trop d'invocation de recherche, on annule la recherche\n");
        return 0;
    }     
    for (int ligne = 0 ; ligne < 9 ; ligne ++){
        for (int colonne = 0 ; colonne < 9 ; colonne ++){
            if (grille[ligne][colonne] == ' '){
                // cette case est a trouver 
                for (int val = '1' ; val <= '9' ; val++){
                    printf("solve => test de %c en %d,%d\n", val, lig, col);
                    //if (testJeu(grille,ligne, colonne, val, 1) == 1){   // mode silence
                    if (testJeu(grille,ligne, colonne, val, 0) == 1){   // mode bavard
                        grille[ligne][colonne] = val;
                        if (calculSolve(grille, ligne, colonne) == 0){
                            //printf("solve => %c NOK en %d,%d\n", val, ligne, colonne);
                            grille[ligne][colonne] = grilleInitiale[ligne*9+colonne];
                        } else {
                            //("solve => %c OK en %d,%d\n", val, ligne, colonne);
                            if ((ligne == lastLigne) && (colonne == lastColonne)) {
                                printf(".");
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
                //printf("solve => NOK : on a teste toutes les valeurs possibles pour la case %d,%d \n", ligne, colonne);
                grille[ligne][colonne] = grilleInitiale[ligne*9+colonne];
                return 0;
            }
        }
    }
    if (nbSolutions >= 1){
        printf("solve => nb solutions trouvees : %d \n", nbSolutions);
        return 1;
    } else {
      printf("solve => pas de solutions trouvees fin \n");
      return 0;
    }
}

//--------------------------------------------------------
//
//          I N I T S O L V E
//
//--------------------------------------------------------
void initSolve(void){
    nbSolveInvocations = 0;
    nbSolutions = 0;

    initGrilleInitiale();
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
    calculSolve(grille, 0, 0);
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
