//
//      generateur.c
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/grille.h"
#include "../inc/partie.h"
#include "../inc/solve.h"

int isInit = 0;
long graineRandom;
int nbInvocations;

//--------------------------------------------------------
//
//          I N I T
//
//--------------------------------------------------------
void initGenerateur(char **grille){
    if (isInit == 0){
        //printf("generateur.init => debut\n");
        // le générateur n'est pas encore initialisé
        // on initialise les variables globales
        // on initialise le generateur de chiffres aleatoire
        graineRandom = time(NULL) * 20431;
        // on initialise une grille vide
        grilleResetAll(grille);
        initGrilleInitiale();
        //printf("generateur.init => grille vide generee\n");

        //initGrilleInitiale();
        // on reset le nombre d'invocations
        nbInvocations = 0;
        // on ne refait pas l'init la prochaine fois
        isInit = 1; 
        //printf("generateur.init => fin\n");
    } else {
        //printf("generateur.init -> rien a faire\n");
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
        val = val + '0' - 1;
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
//          C A L C U L G E N E R A T E U R
//
//--------------------------------------------------------
int calculGenerateur(char **grille, char **grilleTmp){
    int nbSolutions = 0;
    int finBoucle;
    while (nbSolutions != 1){
        printf("generateur.calculGenerateur => on genere un num lig et col aleatoire\n");
        // on positionne une case au hasard dans la grille
        finBoucle = 100;
        while (finBoucle-- > 0){
            int lig = getRandomValue();
            int col = getRandomValue();
            printf("generateur.calculGenerateur => %d : generation aleatroire test valeurs lig=%d ,col=%d \n",finBoucle, lig, col);
            if (grilleTmp[lig][col] == ' '){
                // la case est vide on met une valeur aleatoire
                char val = getRandomValue() + '1';
                printf("generateur.calculGenerateur => lig=%d, col=%d, val= %c\n", lig, col, val);
                if (testJeu(grilleTmp, lig + 1, col + 1, val, 0) == 1){
                    grille[lig][col] = val;
                    finBoucle = 0;
                }
            } else {
                printf("generateur.calculGenerateur => la cese %d,%d n'est pas vide (%c)\n",lig, col, grilleTmp[lig][col]);
            }
        }

        afficheGrille(grilleTmp);

        printf("generateur.calculGenerateur => debut boucle de generation\n");
        nbSolutions = solve(grilleTmp, 0);
        if (nbSolutions > 1){
            // trop de solutions trouvées, on continue d'ajouter des valeurs dans la grille
            printf("generateur.calculGenerateur => Grille avec %d solutions, on continue en remplissant une nouvelle case\n", nbSolutions);
            calculGenerateur(grille, grilleTmp);
        } else if (nbSolutions == 0) {
            // plus aucune solution avec cete grille
            // il faut changer la valeur de la derniere 
        }
    }
    return 0;
}


//--------------------------------------------------------
//
//          A J O U T E U N E V A L E U R
//
//--------------------------------------------------------
void ajouteUneValeur(char **grille){
    int finBoucle = 0;
    int lig, col;
    printf("ajouteUneValeur -> debut\n");
    while (finBoucle == 0){
        lig = getRandomValue();
        col = getRandomValue();
        char value = '0';
        if (grille[lig][col] == ' '){
            value = getRandomValue() + '1';
            printf("ajouteUneValeur -> test %c en %d,%d\n", value, lig, col);
            if (testJeu(grille, lig, col, value, 1) == true){
                finBoucle = 1;
                grilleSetValeur(grille, lig, col, value);
                printf("ajouteUneValeur -> testJeu OK : ajout de %c en %d,%d\n", value, lig, col);
            } else {
                printf("ajouteUneValeur -> testJeu KO pour %c en %d,%d\n", value, lig, col);
            }
        } else {
            printf("ajouteUneValeur -> la case %d,%d n'est pas vide (%c)\n", lig, col, value);
        }
    }
    printf("ajouteUneValeur -> fin\n");
}

//--------------------------------------------------------
//
//          G E N E R A T E U R
//
//--------------------------------------------------------
int generateur(char **grille){
    int nbSolutions = 0;
    int nbTentatives = 100;
    bool finDeBoucle = false;

    initGenerateur(grille);
    while (!finDeBoucle){
        printf("generateur -> tentative %d\n", nbTentatives);
        nbTentatives--;

        printf("generateur -> ajoute une valeur debut\n");
        afficheGrille(grille);

        ajouteUneValeur(grille);
        afficheGrille(grille);
        printf("generateur -> ajoute une valeur fin\n");

        char **grilleTmp = grilleNew();
        copieGrille(grille, grilleTmp);
        nbSolutions = solve(grilleTmp, false);
        grilleDelete(grilleTmp);
        printf("generateur -> fin de boucle nbSolutions = %d ; nbTentatives = %d\n", nbSolutions, nbTentatives);
        if (nbInvocations <= 0) finDeBoucle = true;
        if (nbSolutions == 1) finDeBoucle = true;

        //getchar();
    }
    afficheGrille(grille);
    return nbSolutions;
}

//--------------------------------------------------------
//
//          G E N E R A T E U R
//
//--------------------------------------------------------
int generateurOld(char **grille){
    char listeValeur[10];
    char **grilleTmp;

    initGenerateur(grille);
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

    int nbSolutions = calculGenerateur(grille, grilleTmp);

    // liberation de la mémoire allouée
    printf("generateur => on desalloue la memoire de grilleTmp\n");
    for (int i = 0 ; i < 9 ; i++){
        free(grilleTmp[i]);
    }
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