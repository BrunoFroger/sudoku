//
//      grille.c
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../inc/fichiers.h"
#include "../inc/couleurs.h"
#include "../inc/grille.h"


char grilleInitiale[TAILLEGRILLE][TAILLEGRILLE];

int lastLigne=8;
int lastColonne=8;

//--------------------------------------------------------
//
//          I N I T G R I L L E I N I T I A L E
//
//--------------------------------------------------------
void initGrilleInitiale(void){
    //int index = 0;

    for (int i = 0 ; i < TAILLEGRILLE ; i++){
        for (int j = 0 ; j < TAILLEGRILLE ; j++){
            grilleInitiale[i][j] = ' ';
        }
    }
    /*
    while (index < 81){
        //printf("grille.initGrilleInitiale => reset de la case %d \n", index);
        grilleInitiale[index] = ' ';
        index++;
    }
    */
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
bool grilleDelete(char **grille){
    //printf("grille => on desalloue la memoire de grille\n");
    if (grille != NULL){
        //printf("grille => la grille existe, on la detruit\n");
        for (int i = 0 ; i < 9 ; i++){
            if (grille[i] == NULL){
                //printf("grille => destruction de la ligne %d impossible\n",i);
                return false;
            }
            //printf("grille => destruction de la ligne %d\n",i);
            free(grille[i]);
        }
        //printf("grille => destruction du pointeur general\n");
        free(grille);
        return true;
    } 
    return false;
}

//--------------------------------------------------------
//
//          G R I L L E S E T V A L E U R
//
//--------------------------------------------------------
bool grilleSetValeur(char **grille, int ligne, int colonne, char valeur){
    if (grille == NULL){
        return false;
    } else {
        if (grilleInitiale[ligne][colonne] != ' '){
            printf("Erreur : Impossible de modifier une valeur initiale <%c en %d,%d>\n", valeur, ligne, colonne);
            //getchar();
            return false;
        }
        grille[ligne][colonne] = valeur;
        return true;
    }
}

//--------------------------------------------------------
//
//          G R I L L E R E S E T V A L E U R
//
//--------------------------------------------------------
bool grilleResetValeur(char **grille, int ligne, int colonne){
    if (grille == NULL){
        return false;
    } else {
        grille[ligne][colonne] = grilleInitiale[ligne][colonne];
    }
    return true;
}

//--------------------------------------------------------
//
//          G R I L L E R E S E T A L L
//
//--------------------------------------------------------
bool grilleResetAll(char **grille){
    if (grille == NULL){
        return false;
    } else {
        for (int lig = 0 ; lig < NBLIGNES ; lig++){
            for (int col = 0 ; col < NBCOLONNES ; col++){
                grilleResetValeur(grille, lig, col);
            }
        }
    }
    return true;
}

//--------------------------------------------------------
//
//          G R I L L E S E T I N I T I A L E
//
//--------------------------------------------------------
bool grilleSetInitiale(char **grille){
    if (grille == NULL){
        return false;
    } else {
        for (int lig = 0 ; lig < NBLIGNES ; lig++){
            for (int col = 0 ; col < NBCOLONNES ; col++){
                grilleInitiale[lig][col] = grille[lig][col];
            }
        }
    }
    return true;
}

//--------------------------------------------------------
//
//          G R I L L E L O A D I N I T I A L E
//
//--------------------------------------------------------
bool grilleLoadInitiale(char **grille){
    if (grille == NULL){
        return false;
    } else {
        for (int lig = 0 ; lig < NBLIGNES ; lig++){
            for (int col = 0 ; col < NBCOLONNES ; col++){
                grille[lig][col] = grilleInitiale[lig][col];
            }
        }
    }
    return true;
}

//--------------------------------------------------------
//
//          G R I L L E T E S T V A L E U R
//
//--------------------------------------------------------
bool grilleTestValeur(char **grille, int ligne, int colonne, char valeur){
    if (grille == NULL){
        return false;
    } else {
        if (grille[ligne][colonne] != valeur){
            return false;
        }
    }
    return true;
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
bool testListeValide(char *liste){
    for (int idx = 0 ; idx < TAILLEGRILLE - 1 ; idx++){
        if (liste[idx] != ' '){
            for (int idx2 = idx + 1; idx2 < TAILLEGRILLE ; idx2++){
                if (liste[idx] == liste[idx2]){
                    return false;
                }
            }
        }
    }
    return true;
}

//--------------------------------------------------------
//
//          G R I L L E T E S T L I G N E V A L I D E
//
//--------------------------------------------------------
bool grilleTestLigneValide(char **grille, int ligne){
    if (grille == NULL){
        return false;
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
bool grilleTestColonneValide(char **grille, int colonne){
    if (grille == NULL){
        return false;
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
bool grilleTestRegionValide(char **grille, int ligneRegion, int colonneRegion){
    if (grille == NULL){
        return false;
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

//--------------------------------------------------------
//
//          G R I L L E V A L I D E
//
//--------------------------------------------------------
bool grilleValide(char **grille, bool silence){
    for (int lig = 0 ; lig < TAILLEGRILLE ; lig++){
        if (grilleTestLigneValide(grille,lig) == false) {
            if (!silence) printf("grilleValide => erreur : la ligne %d n'est pas valide\n", lig+1);
            return false;
        }
    }
    for (int col = 0 ; col < TAILLEGRILLE ; col++){
        if (grilleTestColonneValide(grille,col) == false){
            if (!silence) printf("grilleValide => erreur : la colonne %d n'est pas valide\n", col+1);
            return false;
        }
    }
    for (int ligneRegion = 0 ; ligneRegion < TAILLEGRILLE/3 ; ligneRegion++){
        for (int colonneRegion = 0 ; colonneRegion < TAILLEGRILLE/3 ; colonneRegion++){
            if (grilleTestRegionValide(grille, ligneRegion, colonneRegion) == false){
                if (!silence) printf("grilleValide => erreur : la region %d,%d n'est pas valide\n", ligneRegion+1, colonneRegion+1);
                return false;
            }
        }
    }
    return true;
}

//--------------------------------------------------------
//
//          G R I L L E P L E I N E
//
//--------------------------------------------------------
bool grillePleine(char **grille){
    for (int ligne = 0 ; ligne < TAILLEGRILLE ; ligne++){
        for (int colonne = 0 ; colonne < TAILLEGRILLE ; colonne++){
            if (grille[ligne][colonne] == ' '){
                return false;
            }
        }
    }
    return true;
}

//--------------------------------------------------------
//
//         A F F I C H E G R I L L E
//
//--------------------------------------------------------
void afficheGrille(char **grille){
    printf("\n");
    printf("    1   2   3    4   5   6    7   8   9\n");
    printf("  +---+---+---++---+---+---++---+---+---+\n");
    for (int ligne = 0 ; ligne < 9 ; ligne++){
        printf("%d |", ligne + 1);
        for (int colonne = 0 ; colonne < 9 ; colonne++){
            if (grilleInitiale[ligne][colonne] != ' '){
                couleur("31");
            }
            printf(" %c ",grille[ligne][colonne]);
            couleur("0");
            printf("|");
            if ((colonne == 2) || (colonne == 5)) printf("|");
        }
        printf("\n");
        printf("  +---+---+---++---+---+---++---+---+---+\n");
        if ((ligne == 2) || (ligne == 5)) printf("  +---+---+---++---+---+---++---+---+---+\n");
    }
}

//--------------------------------------------------------
//
//         C O M P A R E G R I L L E
//
//--------------------------------------------------------
bool compareGrille(char **grille1, char **grille2){
    for (int ligne = 0 ; ligne < TAILLEGRILLE ; ligne++){
        for (int colonne = 0 ; colonne < TAILLEGRILLE ; colonne++){
            if (grille1[ligne][colonne] != grille2[ligne][colonne]) return false;
        }
    }
    return true;
}

//--------------------------------------------------------
//
//         C O P I E G R I L L E
//
//--------------------------------------------------------
void copieGrille(char **grilleOrigine, char **grilleDestination){
    for (int ligne = 0 ; ligne < TAILLEGRILLE ; ligne++){
        for (int colonne = 0 ; colonne < TAILLEGRILLE ; colonne++){
            grilleDestination[ligne][colonne] = grilleOrigine[ligne][colonne];
        }
    }
}


//--------------------------------------------------------
//
//         A F F I C H E G R I L L E I N I T I A L E
//
//--------------------------------------------------------
void afficheGrilleInitiale(void){
    char **grilleTmp = grilleNew();
    for (int i = 0 ; i < TAILLEGRILLE ; i++){
        for (int j = 0 ; j < TAILLEGRILLE ; j++){
            grilleTmp[i][j] = grilleInitiale[i][j];
        }
    }
    afficheGrille(grilleTmp);
    grilleDelete(grilleTmp);
}
