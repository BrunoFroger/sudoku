//
//      chargePartie.c
//

#include <stdio.h>

int chargePartie(char grille[9][9]){
    char nomFichier[30];
    FILE *fichier;
    printf("Nom du fichier à lire : ");
    scanf("%s",nomFichier);
    fichier = fopen(nomFichier,"r");
    if (fichier != NULL){
        printf("Chargement du fichier %s \n",nomFichier);
        for (int ligne = 0 ; ligne < 9 ; ligne ++){
            for (int colonne = 0 ; colonne < 9 ; colonne ++){
                grille[ligne][colonne] = fgetc(fichier);
            }
        }
        fclose(fichier);
        return 1;
    }else {
        printf("fichier %s inconnu\n", nomFichier);
        return 0;
    }
}
