//
// sauvegarde.c
//


#include <stdio.h>

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
