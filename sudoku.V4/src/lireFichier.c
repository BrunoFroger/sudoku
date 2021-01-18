//
//      lireFichier.c
//

#include <stdio.h>
#include "../inc/grille.h"

//--------------------------------------------------------
//
//          L I R E F I C H I E R
//
//--------------------------------------------------------
int lireFichier(char *nomFichier, char **grille){
    FILE *fichier;
    char car;
    char filename[30];
    initGrilleInitiale();
    sprintf(filename,"grilles/%s",nomFichier);
    fichier = fopen(filename,"r");
    if (fichier != NULL){
        printf("Chargement du fichier %s \n",nomFichier);
        for (int ligne = 0 ; ligne < 9 ; ligne ++){
            for (int colonne = 0 ; colonne < 9 ; colonne ++){
                //printf("lireFichier => car lu en %d,%d = %c\n",ligne, colonne, car);
                car = fgetc(fichier);
                grille[ligne][colonne] = car;
                grilleInitiale[ligne*9+colonne] = car;
            }
        }
        fclose(fichier);
        return 1;
    }else {
        printf("fichier %s inconnu\n", nomFichier);
        return 0;
    }
}
