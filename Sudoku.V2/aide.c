//
//      aide.c
//

#include <stdio.h>

#define TAILLE_LIGNE    100
#define FICHIER_AIDE    "regleDuJeu.txt"

void aide(void){
    FILE *fichier;
    char ligne[TAILLE_LIGNE];

    //printf("afficher regles du jeu\n");
    fichier = fopen(FICHIER_AIDE, "r");
    if (fichier == NULL){
        printf("ERREUR : le fichier %s n'existe pas\n", FICHIER_AIDE);
        return;
    }
    printf("\n");
    while (!feof(fichier)){
        fgets(ligne, TAILLE_LIGNE, fichier);
        printf("%s",ligne);
    }
    printf("\n");
}
