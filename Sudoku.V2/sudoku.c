//
//  sudoku.c
//

#include <stdio.h>


// definition des fonctions
#include "nouvellePartie.h"
#include "jouePartie.h"
#include "aide.h"
#include "chargePartie.h"

int main(void){

    // initialisation des variables
    char choixMenu = ' ';
    char tmpSaisie[5];

    printf("+----------------------------+\n");
    printf("|        Jeu de sudoku       |\n");
    printf("+----------------------------+\n");
    printf("Auteur : Simon Froger\n\n");
    // affichage du menu de choix
    while (choixMenu != '4'){
        printf("\nMenu principal\n");
        printf("1 : Nouvelle partie\n");
        printf("2 : Charger une partie sauvegardée\n");
        printf("3 : Aide\n");
        printf("4 : Quitter\n");
        printf("votre choix : ");
        scanf("%s",tmpSaisie);
        choixMenu=tmpSaisie[0];
        //scanf("%c",&choixMenu);

        // evaluation de la valeur choisie
        if (choixMenu == '1'){
            nouvellePartie();
        } else if (choixMenu == '2'){
            char grille[9][9];
            if (chargePartie(grille) != 0){
                jouePartie(grille);
            }
        } else if (choixMenu == '3'){
            aide();
        } else if (choixMenu == '4'){
            printf("fin de partie\n");
        } else {
            printf("valeur Erronée\n");
        }
    }
}
