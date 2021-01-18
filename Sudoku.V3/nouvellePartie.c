//
//  nouvellePartie.c
//


#include <stdio.h>
#include <string.h>

#include "jouePartie.h"
#include "lireFichier.h"

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
