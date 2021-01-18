//
// sauvegarde.c
//


#include <stdio.h>

void sauvegarde(char grille[9][9]){
    char sauvegarde[30];
    FILE *fichier;
    printf("voulez vous sauvegarder votre partie (oui/non) ? ");
    scanf("%s", sauvegarde);
    if (sauvegarde[0] != 'o'){
        return;
    } else {
        printf("Nom du fichier de sauvegarde : ");
        scanf("%s",sauvegarde);
        fichier = fopen(sauvegarde, "w");
        for (int ligne = 0 ; ligne < 9 ; ligne ++){
            for (int colonne = 0 ; colonne < 9 ; colonne ++){
                fputc(grille[ligne][colonne], fichier);
            }
        }
        fclose(fichier);
    }
}
