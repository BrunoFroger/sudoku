//
//      generateur.c
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "solve.h"
#include "afficheGrille.h"
#include "testJeu.h"

int isInit = 0;
long graineRandom;
int nbInvocations;

//--------------------------------------------------------
//
//          I N I T
//
//--------------------------------------------------------
void init(char **grille){
    if (isInit == 0){
        printf("generateur.init => debut\n");
        // le générateur n'est pas encore initialisé
        // on initialise les variables globales
        // on initialise le generateur de chiffres aleatoire
        graineRandom = time(NULL) * 20431;
        // on initialise une grille vide
        for (int lig = 0 ; lig < 9 ; lig++){
            for (int col = 0 ; col < 9 ; col++){
                grille[lig][col] = ' ';
            }
        }
        // on reset le nombre d'invocations
        nbInvocations = 0;
        // on ne refait pas l'init la prochaine fois
        isInit = 1; 
        printf("generateur.init => fin\n");
    }
}

//--------------------------------------------------------
//
//          G E T R A N D O M V A L U E
//
//--------------------------------------------------------
int getRandomValue(void){
    int val;
    graineRandom = (graineRandom * 65539) % 2147483648;
    val = graineRandom * 9 / 2147483648;   // genere un nombre entre 0 et 8
    return val;
}

//--------------------------------------------------------
//
//          G E N E R E L I S T E V A L E U R
//
//--------------------------------------------------------
void genereListeValeur(char *liste){
    int i = 0;
    int valOk;

    while (i < 9){
        int val = getRandomValue();   // genere un nombre entre 0 et 8
        val = val + '0';
        valOk = 1;
        for (int j = 0 ; j < i ; j++){
            if (liste[j] == val){
                valOk = 0;
            }
        }
        if (valOk == 1){
            liste[i++]=val;
            liste[i] = 0;
        }
    }
}

//--------------------------------------------------------
//
//          G E N E R A T E U R
//
//--------------------------------------------------------
int generateur(char **grille){
    char listeValeur[10];
    int nbSolutions = 0;
    char **grilleTmp;
    int finBoucle;

    init(grille);
    getchar();
    printf("-----------------------------------\n");
    printf("generateur => invocation %d\n",nbInvocations++);
    genereListeValeur(listeValeur);
    printf("generateur => liste aleatoire de valeurs = %s\n", listeValeur);
    // allocation de la memoire pour la grille temporaire
    // avec recopie de grille dans grilleTmp
    printf("generateur => allocation memoire grilleTmp debut\n");
    grilleTmp = malloc(9 * sizeof(char*));
    for (int i = 0 ; i < 9 ; i++){
        grilleTmp[i]=malloc(9 * sizeof(char));
        for (int j = 0 ; j < 9 ; j++){
            grilleTmp[i][j] = grille[i][j];
        }
    }
    printf("generateur => allocation memoire grilleTmp fin\n");

    while (nbSolutions != 1){
        printf("generateur => on genere un num lig et col aleatoire\n");
        // on positionne une case au hasard dans la grille
        finBoucle = 100;
        while (finBoucle-- > 0){
            int lig = getRandomValue();
            int col = getRandomValue();
            printf("generateur => %d : generation aleatroire test valeurs lig=%d ,col=%d \n",finBoucle, lig, col);
            if (grilleTmp[lig][col] == ' '){
                // la case est vide on met une valeur aleatoire
                char val = getRandomValue() + '1';
                printf("generateur => lig=%d, col=%d, val= %c\n", lig, col, val);
                if (testJeu(grilleTmp, lig, col, val, 0) == 1){
                    grilleTmp[lig-1][col-1] = val;
                    grille[lig-1][col-1] = val;
                    finBoucle = 0;
                }
            } else {
                printf("generateur => la cese %d,%d n'est pas vide (%c)\n",lig, col, grilleTmp[lig][col]);
            }
        }

        afficheGrille(grilleTmp);

        printf("generateur => debut boucle de generation\n");
        nbSolutions = solve(grilleTmp, 0);
        if (nbSolutions > 1){
            // trop de solutions trouvées, on continue d'ajouter des valeurs dans la grille
            printf("Grille avec %d solutions, on continue en remplissant une nouvelle case\n", nbSolutions);
            generateur(grille);
        } else if (nbSolutions == 0) {
            // plus aucune solution avec cete grille
            // il faut changer la valeur de la derniere 
        }

    }
    /*
    for (ligne = 0 ; ligne < 9 ; ligne ++){
        for (colonne = 0 ; colonne < 9 ; colonne ++){
            for (int idxVal = 0 ; idxVal < 9 ; idxVal++){
                grilleTmp[ligne][colonne] = listeValeur[idxVal];
                afficheGrille(grilleTmp);
                nbSolutions = solve(grilleTmp,1);
                if (nbSolutions == 1){
                    printf("generateur => on a trouve une grille valide\n");
                    // on recopie la grille 
                    for (int i = 0 ; i < 9 ; i++){
                        grilleTmp[i]=malloc(9 * sizeof(char));
                        for (int j = 0 ; j < 9 ; j++){
                            grille[i][j] = grilleTmp[i][j];
                        }
                    }
                    return 1;
                } else {
                    printf("Cette grille est invalide nb solutions = %d\n",nbSolutions);
                    // on lance le générateur 
                }
                getchar();getchar();    
                // liberation de la mémoire allouée
                for (int i = 0 ; i < 9 ; i++){
                    free(grilleTmp[i]);
                }
                free(grilleTmp);
            }
        }
    }*/
    // liberation de la mémoire allouée
    for (int i = 0 ; i < 9 ; i++){
        free(grilleTmp[i]);
    }
    printf("generateur => on desalloue la memoire de grilleTmp\n");
    free(grilleTmp);
    return nbSolutions;
}


/*
Fonction generation  (parametre :  grille , nbCases) retourne une  grille
    copier grille dans newGrille 
    Pour chaque case C encore  vide  de  newGrille 
        Pour chaque valeur V du domaine de  la  case C
            affecter V a C
            Si (resoudre = 1) 
                Si( nbCases=0)
                    retourner newGrille
                Sinon 
                    tmpGrille := generation (newGrille, nbCases−1)
                    Si (tmpGrille<>rien )
                        retourner tmpGrille
            Si( resoudre > 1)
                tmpGrille := generation (newGrille, nbCases−1)
                Si (tmpGrille<>rien)
                    retourner tmpGrille
    retourner rien
*/