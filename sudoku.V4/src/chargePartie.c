//
//      chargePartie.c
//

#include <stdio.h>
#include "../inc/lireFichier.h"

//--------------------------------------------------------
//
//          C H A R G E P A R T I E
//
//--------------------------------------------------------
int chargePartie(char **grille){
    char nomFichier[30];
    printf("Nom du fichier à lire : ");
    scanf("%s",nomFichier);
    return lireFichier(nomFichier,grille);
}
