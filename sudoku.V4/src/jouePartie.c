//
//      jouePartie.c
//


#include <stdio.h>
#include <string.h>

#include "../inc/afficheGrille.h"
#include "../inc/sauvegarde.h"
#include "../inc/testJeu.h"
#include "../inc/aide.h"
#include "../inc/solve.h"
#include "../inc/grille.h"


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
            int nbSolutions = solve(grille,0);
            if (nbSolutions != 0){
                printf("Il existe %d solutions a cette grille\n",nbSolutions);
            }
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
            //printf("jouePartie-jeu => saisie = <%s>, ligne = <%d>, colonne = <%d> => valeur = <%c>\n", saisie, ligne, colonne, valeur);

            if (testJeu(grille, ligne, colonne, valeur, 0) == 1){
                grille[ligne][colonne] = valeur;
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
