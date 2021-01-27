//
//      solve.c
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "../inc/partie.h"
#include "../inc/grille.h"

#define NB_MAX_INVOCATIONS  100000

int nbSolveInvocations = 0;
int nbSolutions = 0;
clock_t clockTime;
char **grilleResultat;

//--------------------------------------------------------
//
//          C A L C U L S O L V E
//
//--------------------------------------------------------
bool calculSolve(char **grille, int lig, int col, bool silence){
    //printf("===============================================================\n");
    //printf("solve => debut recherche de solution de la grille en %d,%d\n", lig, col);
    if (!silence){
        afficheGrille(grille);
        getchar();
    }
    nbSolveInvocations++;
    if (nbSolveInvocations > NB_MAX_INVOCATIONS) { // trop d'iterations sans resultats, on annule la recherche
        printf("trop d'invocation de recherche (%d), on annule la recherche\n", NB_MAX_INVOCATIONS);
        return false;
    }     
    for (int ligne = 0 ; ligne < 9 ; ligne ++){
        for (int colonne = 0 ; colonne < 9 ; colonne ++){
            if (grille[ligne][colonne] == ' '){
                // cette case est a trouver 
                for (int val = '1' ; val <= '9' ; val++){
                    if (!silence) printf("solve => test de %c en %d,%d\n", val, ligne, colonne);
                    if (testJeu(grille,ligne, colonne, val, silence) == true){   // mode normal
                    //if (testJeu(grille,ligne, colonne, val, false) == true){   // mode bavard
                        grille[ligne][colonne] = val;
                        if (calculSolve(grille, ligne, colonne, silence) == false){
                            if (!silence) printf("solve => %c NOK en %d,%d\n", val, ligne, colonne);
                            grille[ligne][colonne] = grilleInitiale[ligne][colonne];
                        } else {
                            if (!silence) printf("solve => %c OK en %d,%d\n", val, ligne, colonne);
                            //if ((ligne == lastLigne) && (colonne == lastColonne)) {
                            if (grillePleine(grille)){ 
                                if (!silence) printf(".");
                                nbSolutions ++;
                            }
                            // on sauvegarde cette grille comme resultat
                            for (int i = 0 ; i < 9 ; i++){
                                for (int j = 0 ; j < 9 ; j++){
                                    grilleResultat[i][j] = grille[i][j];
                                }
                            }
                        }
                    }
                }
                //printf("solve => NOK : on a teste toutes les valeurs possibles pour la case %d,%d \n", ligne, colonne);
                grille[ligne][colonne] = grilleInitiale[ligne][colonne];
                return false;
            }
        }
    }
    if (nbSolutions >= 0){
        printf("solve => nb solutions trouvees : %d \n", nbSolutions);
        return true;
    } else {
      printf("solve => pas de solutions trouvees fin \n");
      return false;
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
int solve(char **grille, bool modeSilence){
    clockTime = clock();

    // allocation de la memoire pour la grille de jeu
    grilleResultat = grilleNew();
    initSolve();
    //calculSolve(grille, 0, 0, modeSilence);
    calculSolve(grille, 0, 0, modeSilence);
    clockTime = clock() - clockTime;
    if (!modeSilence){
        printf("\n");
        bilanSolve();
    }
    // restauration de la grille resultat dans la grille
    for (int i = 0 ; i < 9 ; i++){
        for (int j = 0 ; j < 9 ; j++){
            grille[i][j]= grilleResultat[i][j];
        }
    }  
    // liberation de la mémoire allouée
    grilleDelete(grilleResultat);
    return nbSolutions;
}
