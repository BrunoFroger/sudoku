//
//  nouvellePartie.c
//


#include <stdio.h>
#include "grillesModeles.h"
#include "jouePartie.h"

void nouvellePartie(void){
    char tmpSaisie[5];
    char niveauPartie;
    printf("selection du niveau de jeu\n");
    printf("a : Facile\n");
    printf("b : Intermédiaire\n");
    printf("c : Expert\n");
    printf("votre choix : ");
    scanf("%s",tmpSaisie);
    printf("\n");
    niveauPartie=tmpSaisie[0];
    //niveauPartie = getchar();
    if (niveauPartie == 'a'){
        jouePartie(partieFacile);
    } else if (niveauPartie == 'b'){
        jouePartie(partieIntermediaire);
    } else if (niveauPartie == 'c'){
        jouePartie(partieExpert);
    } else {
        printf("valeur Erronée\n");
    }
}
