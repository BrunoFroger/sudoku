//
//      fichiers.c
//

#include <stdio.h>
#include <stdbool.h>

#include "../inc/grille.h"

//--------------------------------------------------------
//
//          L I R E F I C H I E R
//
//--------------------------------------------------------
bool lireFichier(char *nomFichier, char **grille){
    FILE *fichier;
    char car;
    char filename[50];
    initGrilleInitiale();
    sprintf(filename,"grilles/%s",nomFichier);
    fichier = fopen(filename,"r");
    if (fichier != NULL){
        //printf("Chargement du fichier %s \n",nomFichier);
        for (int ligne = 0 ; ligne < TAILLEGRILLE ; ligne ++){
            for (int colonne = 0 ; colonne < 9 ; colonne ++){
                //printf("lireFichier => car lu en %d,%d = %c\n",ligne, colonne, car);
                car = fgetc(fichier);
                grille[ligne][colonne] = car;
                grilleInitiale[ligne][colonne] = car;
            }
        }
        fclose(fichier);
        return true;
    }else {
        printf("fichier %s inconnu\n", nomFichier);
        return false;
    }
}

//--------------------------------------------------------
//
//          S A U V E G A R D E
//
//--------------------------------------------------------
void sauvegarde(char **grille){
    char sauvegarde[30];
    char tmp[30];
    FILE *fichier;
    printf("voulez vous sauvegarder votre partie (oui/non) ? ");
    scanf("%s", sauvegarde);
    if (sauvegarde[0] != 'o'){
        return;
    } else {
        printf("Nom du fichier de sauvegarde : ");
        scanf("%s",tmp);
        sprintf(sauvegarde,"grilles/%s",tmp);
        fichier = fopen(sauvegarde, "w");
        for (int ligne = 0 ; ligne < 9 ; ligne ++){
            for (int colonne = 0 ; colonne < 9 ; colonne ++){
                fputc(grille[ligne][colonne], fichier);
            }
        }
        fclose(fichier);
    }
}
