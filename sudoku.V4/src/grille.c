//
//      grille.c
//

#include <stdio.h>
#include <stdlib.h>

#include "../inc/lireFichier.h"

#define TAILLEGRILLE    9
#define NBLIGNES        TAILLEGRILLE
#define NBCOLONNES      TAILLEGRILLE

char grilleInitiale[81] = 
        {
            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',
            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',
            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',

            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',
            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',
            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',

            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',
            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',
            ' ', ' ', ' ',      ' ', ' ', ' ',      ' ', ' ', ' ',
        };

int lastLigne=8;
int lastColonne=8;

//--------------------------------------------------------
//
//          I N I T G R I L L E I N I T I A L E
//
//--------------------------------------------------------
void initGrilleInitiale(void){
    int index = 0;

    while (index < 81){
        //printf("grille.initGrilleInitiale => reset de la case %d \n", index);
        grilleInitiale[index] = ' ';
        index++;
    }
}

//--------------------------------------------------------
//
//          I N I T G R I L L E I N I T I A L E
//
//--------------------------------------------------------
void initGrilleInitialeOld(void){
    int index = 81;
    char car;

    while ((car = grilleInitiale[--index]) != ' '){
        //printf("grille.initGrilleInitiale => test de la case %d(%c) \n", index, car);
        lastColonne--;
        if (lastColonne < 0){
            lastColonne = 8;
            lastLigne--;
        }
    }
}

//--------------------------------------------------------
//
//          G R I L L E N E W
//
//--------------------------------------------------------
char **grilleNew(void){
    char **grille;
    //printf("grille => allocation memoire grille debut\n");
    grille = malloc(9 * sizeof(char*));
    if (grille != NULL){
        for (int i = 0 ; i < 9 ; i++){
            grille[i]=malloc(9 * sizeof(char));
            if (grille[i] != NULL){
                for (int j = 0 ; j < 9 ; j++){
                    grille[i][j] = ' ';
                }
            } else {
                return NULL;
            }
        }
    } else {
        return NULL;
    }
    return grille;
}

//--------------------------------------------------------
//
//          G R I L L E D E L E T E
//
//--------------------------------------------------------
int grilleDelete(char **grille){
    //printf("generateur => on desalloue la memoire de grilleTmp\n");
    if (grille != NULL){
        for (int i = 0 ; i < 9 ; i++){
            if (grille[i] == NULL){
                return -1;
            }
            free(grille[i]);
        }
        free(grille);
        return 0;
    } else {
        return -1;
    }
}

//--------------------------------------------------------
//
//          G R I L L E S E T V A L E U R
//
//--------------------------------------------------------
int grilleSetValeur(char **grille, int ligne, int colonne, char valeur){
    if (grille == NULL){
        return -1;
    } else {
        grille[ligne][colonne] = valeur;
        return 0;
    }
}

//--------------------------------------------------------
//
//          G R I L L E R E S E T V A L E U R
//
//--------------------------------------------------------
int grilleResetValeur(char **grille, int ligne, int colonne){
    if (grille == NULL){
        return -1;
    } else {
        grille[ligne][colonne] = ' ';
        return 0;
    }
}

//--------------------------------------------------------
//
//          G R I L L E R E S E T A L L
//
//--------------------------------------------------------
int grilleResetAll(char **grille){
    if (grille == NULL){
        return -1;
    } else {
        for (int lig = 0 ; lig < NBLIGNES ; lig++){
            for (int col = 0 ; col < NBCOLONNES ; col++){
                grilleResetValeur(grille, lig, col);
            }
        }
        return 0;
    }
}

//--------------------------------------------------------
//
//          G R I L L E L O A D I N I T I A L E
//
//--------------------------------------------------------
int grilleLoadInitiale(char **grille){
    if (grille == NULL){
        return -1;
    } else {
        for (int lig = 0 ; lig < NBLIGNES ; lig++){
            for (int col = 0 ; col < NBCOLONNES ; col++){
                grille[lig][col] = grilleInitiale[lig*9+col];
            }
        }
        return 0;
    }
}

//--------------------------------------------------------
//
//          G R I L L E T E S T V A L E U R
//
//--------------------------------------------------------
int grilleTestValeur(char **grille, int ligne, int colonne, char valeur){
    if (grille == NULL){
        return -1;
    } else {
        if (grille[ligne][colonne] != valeur){
            return -1;
        }
        return 0;
    }
}

//--------------------------------------------------------
//
//          D I S P L A Y L I S T E
//
//--------------------------------------------------------
void displayListe(char *liste){
    printf("Liste des valeurs utilisées : ");
    for (int idx = 0 ; idx < TAILLEGRILLE - 1 ; idx ++){
        printf("(%d,%c)\t ", idx, liste[idx]);
    }
    printf("(%d,%c)\n", TAILLEGRILLE - 1, liste[TAILLEGRILLE - 1]);
}

//--------------------------------------------------------
//
//          T E S T L I S T E V A L I D E
//
//--------------------------------------------------------
int testListeValide(char *liste){
    for (int idx = 0 ; idx < TAILLEGRILLE - 1 ; idx++){
        if (liste[idx] != ' '){
            for (int idx2 = idx + 1; idx2 < TAILLEGRILLE ; idx2++){
                if (liste[idx] == liste[idx2]){
                    return -1;
                }
            }
        }
    }
    return 0;
}

//--------------------------------------------------------
//
//          G R I L L E T E S T L I G N E V A L I D E
//
//--------------------------------------------------------
int grilleTestLigneValide(char **grille, int ligne){
    if (grille == NULL){
        return -1;
    } else {
        char listeValeurs[TAILLEGRILLE];
        for (int idx = 0 ; idx < TAILLEGRILLE ; idx++){
            listeValeurs[idx] = grille[ligne][idx];
        }
        //displayListe(listeValeurs);
        return testListeValide(listeValeurs);
    }    
}

//--------------------------------------------------------
//
//          G R I L L E T E S T C O L O N N E V A L I D E
//
//--------------------------------------------------------
int grilleTestColonneValide(char **grille, int colonne){
    if (grille == NULL){
        return -1;
    } else {
        char listeValeurs[TAILLEGRILLE];
        for (int idx = 0 ; idx < TAILLEGRILLE ; idx++){
            listeValeurs[idx] = grille[idx][colonne];
        }
        //displayListe(listeValeurs);
        return testListeValide(listeValeurs);
    }
}

//--------------------------------------------------------
//
//          G R I L L E T E S T R E G I O N V A L I D E
//
//--------------------------------------------------------
int grilleTestRegionValide(char **grille, int ligneRegion, int colonneRegion){
    if (grille == NULL){
        return -1;
    } else {
        int idx = 0;
        char listeValeurs[TAILLEGRILLE];
        for (int ligne = 0 ; ligne < 3 ; ligne++) {
            for (int colonne = 0 ; colonne < 3 ; colonne++){
                listeValeurs[idx++] = grille[ligneRegion * 3 + ligne][colonneRegion * 3 + colonne];
            }
        }
        //displayListe(listeValeurs);
        return testListeValide(listeValeurs);
    }
}
