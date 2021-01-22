//
//      aide.c
//

#include <stdio.h>

#define TAILLE_LIGNE    100
#define FICHIER_AIDE    "regleDuJeu.txt"

//--------------------------------------------------------
//
//          R E G L E D U J E U 
//
//--------------------------------------------------------
void regleDuJeu(void){
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

//--------------------------------------------------------
//
//          A I D E
//
//--------------------------------------------------------
void aide(void){
    printf("+-----------------------------------------------+\n");
    printf("|       commandes disponibles                   |\n");
    printf("+----------------+------------------------------+\n");
    printf("| aide           | cet ecran                    |\n");
    printf("| jeu x,y,v      | joue la valeur v en x,y      |\n");
    printf("| fin            | quitte la partie en cours    |\n");
    printf("| solution       | calcule la solution          |\n");
    printf("| efface x,y     | efface la valeur en x,y      |\n");
    printf("| reset          | efface la grille             |\n");
    printf("+-----------------------------------------------+\n");
}