//
//      partie.c
//

#include <stdio.h>
#include <stdbool.h>

#include "../inc/fichiers.h"

//--------------------------------------------------------
//
//          C H A R G E P A R T I E
//
//--------------------------------------------------------
bool chargePartie(char **grille){
    char nomFichier[30];
    printf("Nom du fichier à lire : ");
    scanf("%s",nomFichier);
    return lireFichier(nomFichier,grille);
}
