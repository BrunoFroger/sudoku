//
//      partie.c
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../inc/fichiers.h"
#include "../inc/grille.h"
#include "../inc/aide.h"
#include "../inc/solve.h"


//--------------------------------------------------------
//
//          C H A R G E P A R T I E
//
//--------------------------------------------------------
bool chargePartie(char **grille){
    char nomFichier[30];
    printf("Nom du fichier à lire : ");
    scanf("%s",nomFichier);
    return lireFichier(nomFichier,grille);
}

//--------------------------------------------------------
//
//          T E S T J E U
//
//--------------------------------------------------------
bool testJeu(char **grille, int ligne, int colonne, char valeur, bool silence){
    if (!silence) printf("partie.c:testJeu => test de %c en %d,%d\n", valeur, ligne, colonne);
    if ((ligne < 0) | (ligne > 8)){
        printf("Erreur : numero de ligne invalide\n");
        return false;
    }
    if ((colonne < 0) | (colonne > 8)){
        printf("Erreur : numero de colonne invalide\n");
        return false;
    }
    if ((valeur < '1') | (valeur > '9')){
        printf("Erreur : numero de colonne invalide\n");
        return false;
    }
    char **grilleTmp = grilleNew();
    copieGrille(grille, grilleTmp);
    bool resultat = false;
    if (grilleSetValeur(grilleTmp, ligne, colonne, valeur) == true) {
        if (grilleValide(grilleTmp,silence) == true){
            resultat = true;
        }
    }
    //afficheGrille(grilleTmp);
    return resultat;

}

/*
//--------------------------------------------------------
//
//          S O L V E
//
//--------------------------------------------------------
bool solve(char **grille, bool silence){
    if (!silence){
        printf("+----------------------------\n");
        printf("|\n");
        printf("|      Solve => debut\n");
        printf("|\n");
        printf("+----------------------------\n");
        //afficheGrille(grille);
        //getchar();
    }
    if (grillePleine(grille)) return true;
    for (int i = 0 ; i < TAILLEGRILLE ; i++){
        for (int j = 0 ; j < TAILLEGRILLE ; j++){
            if (grille[i][j] == ' '){
                for (char val = '1' ; val <= '9' ; val++){
                    if (!silence) printf("solve => test %c en %d,%d \n", val, i, j);
                    grilleSetValeur(grille, i,j,val);
                    if (!silence){
                        //afficheGrille(grille);
                        //getchar();
                    }
                    if (grilleValide(grille,true)){
                        if (!silence) printf("grilleValide => OK\n");
                        if (solve(grille,silence)){
                            if (!silence) printf("return solve true : return true\n");
                            if (grillePleine(grille)) return true;
                            break;
                        } else {
                            if (!silence) printf("return solve false : on continue avec %d,%d\n", i, j);
                            grilleResetValeur(grille, i, j);
                        }
                    } else {
                        if (!silence) printf("grilleValide => : NOK\n");
                        grilleResetValeur(grille, i, j);
                    }
                }
                if (!silence) {
                    printf("solve => on a epuise toutes les valeurs pour la case %d,%d\n", i, j);
                    //afficheGrille(grille);
                    //getchar();
                }
                return false;
            }
        }
        if (!silence) {
            printf("solve => on a fini la ligne %d\n", i);
            //afficheGrille(grille);
            //getchar();
        }
        if (i == 8) getchar();
    }
    return false;
}
*/
//--------------------------------------------------------
//
//          J O U E P A R T I E
//
//--------------------------------------------------------
void jouePartie(char **grille){
    int ligne, colonne;
    char valeur;
    int finJeu= 0;
    char saisie[20];
    char c;
    int idx;

    while (finJeu == 0){
        afficheGrille(grille);
        printf("commande : ");
        //scanf("%d, %d, %c", &ligne, &colonne, &valeur);
        idx = 0;
        while ((c = getchar()) != '\n'){
            if (c != EOF){
                saisie[idx++] = c;
                saisie[idx] = 0;
            }
        }
        if (strlen(saisie) == 0) return;
        //scanf("%s %d,%d,%c",saisie, &ligne, &colonne, &valeur);
        //printf("saisie = %s\n", saisie);
        if (strcmp(saisie,"aide") == 0){
            aide();
        } else if (strncmp(saisie,"reset",5) == 0){
            grilleLoadInitiale(grille);
        } else if (strncmp(saisie,"fin",3) == 0){
            sauvegarde(grille);
            finJeu=1;
        } else if (strncmp(saisie,"solution",8) == 0){
            //int nbSolutions = 
            solve(grille,true);
            //if (nbSolutions != 0){
            //    printf("Il existe %d solutions a cette grille\n",nbSolutions);
            //}
        } else if (strncmp(saisie,"jeu",3) == 0){
            ligne = saisie[4] - '0';
            colonne = saisie[6] - '0';
            valeur = saisie[8];
            if (ligne == 0) {
                sauvegarde(grille);
                return;
            }
            ligne--;        // passage de 1->9 a 0->8
            colonne--;        // passage de 1->9 a 0->8
            printf("jouePartie-jeu => saisie = <%s>, ligne = <%d>, colonne = <%d> => valeur = <%c>\n", saisie, ligne, colonne, valeur);

            if (testJeu(grille, ligne, colonne, valeur, true) == true){
                grilleSetValeur(grille, ligne,colonne, valeur);
            } else {
                printf("erreur : saisie invalide\n");
            }
        } else if (strncmp(saisie,"efface",6) == 0){
            ligne = saisie[7] - '0';
            colonne = saisie[9] - '0';
            ligne--;        // passage de 1->9 a 0->8
            colonne--;        // passage de 1->9 a 0->8
            //printf("jouePartie-efface => saisie = <%s>, ligne = <%d>, colonne = <%d> => valeur = <%c>\n", saisie, ligne, colonne, valeur);
            grilleResetValeur(grille, ligne, colonne);
        } else {
            printf("ERREUR : commande de jeu inconnue (tapez aide)\n");
        }
    }
}

//--------------------------------------------------------
//
//          N O U V E L L E P A R T I E
//
//--------------------------------------------------------
void nouvellePartie(char **grille){
    char tmpSaisie[5];
    char niveauPartie;
    char nomFichier[25];
    printf("selection du niveau de jeu\n");
    printf("a : Facile\n");
    printf("b : Intermédiaire\n");
    printf("c : Expert\n");
    printf("votre choix : ");
    scanf("%s",tmpSaisie);
    printf("\n");
    niveauPartie=tmpSaisie[0];
    //niveauPartie = getchar();
    getchar(); // captation du retour chariot 
    if (niveauPartie == 'a'){
        strcpy(nomFichier, "modeles/grilleFacile");
        lireFichier(nomFichier,grille);
        jouePartie(grille);
    } else if (niveauPartie == 'b'){
        strcpy(nomFichier, "modeles/grilleIntermediaire");
        lireFichier(nomFichier,grille);
        jouePartie(grille);
    } else if (niveauPartie == 'c'){
        strcpy(nomFichier, "modeles/grilleExpert");
        lireFichier(nomFichier,grille);
        jouePartie(grille);
    } else {
        printf("valeur Erronée\n");
    }
}
