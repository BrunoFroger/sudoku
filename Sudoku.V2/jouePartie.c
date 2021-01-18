//
//      jouePartie.c
//


#include <stdio.h>
#include "afficheGrille.h"
#include "sauvegarde.h"
#include "testJeu.h"


void jouePartie(char grille[9][9]){
    int ligne, colonne;
    char valeur;
    int finJeu= 0;
    while (finJeu == 0){
        afficheGrille(grille);
        printf("0,0,0 => quitter\n");
        printf("Votre jeu (ligne, colonne, valeur) : ");
        scanf("%d, %d, %c", &ligne, &colonne, &valeur);
        //printf("ligne = %d, colonne = %d => valeur = %c\n", ligne, colonne, valeur);
        if (ligne == 0) {
            sauvegarde(grille);
            return;
        }
        if (testJeu(grille, ligne, colonne, valeur) == 1){
            grille[ligne - 1][colonne - 1] = valeur;
        }
    }
}
