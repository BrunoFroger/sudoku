//
//  Sudoku.c
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// definition des fonctions
#include "../inc/grille.h"
#include "../inc/fichiers.h"
#include "../inc/aide.h"
#include "../inc/partie.h"

//--------------------------------------------------------
//
//          M A I N
//
//--------------------------------------------------------
int main(int argc, char **argv){

    // initialisation des variables
    char choixMenu = ' ';
    char tmpSaisie[5];
    char **grille;

    // allocation de la memoire pour la grille de jeu
    grille = grilleNew();

    // initialisation de la grille initiale
    initGrilleInitiale();

    printf("+--------------------------------+\n");
    printf("|          Jeu de sudoku         |\n");
    printf("+--------------------------------+\n");
    printf("|  Auteur : Simon Froger (c)2020 |\n");
    printf("+--------------------------------+\n\n");

    // analyse des parametres
    if (argc > 1){
        if (strncmp(argv[1], "genere", 6) == 0){
            //generateur(grille);
            return 0;
        } else {
            lireFichier(argv[1], grille);
            jouePartie(grille);
        }
        //return 0;
    }

    // affichage du menu de choix
    while (choixMenu != '9'){
        printf("\nMenu principal\n");
        printf("1 : Nouvelle partie\n");
        printf("2 : Charger une partie sauvegardée\n");
        printf("3 : Aide\n");
        printf("4 : genere une grille\n");
        printf("5 : affiche partie\n");
        printf("6 : affiche grille initiale\n");
        printf("9 : Quitter\n");
        printf("votre choix : ");
        scanf("%s",tmpSaisie);
        choixMenu=tmpSaisie[0];
        //scanf("%c",&choixMenu);

        // evaluation de la valeur choisie
        switch(choixMenu){
            case '1' :
                // lancement d'une nouvelle partie  
                //nouvellePartie(grille);
                break;
            case '2' :
                // chargement d'une partie existante, sauvegardee
                if (chargePartie(grille) != false){
                    jouePartie(grille);
                }
                afficheGrille(grille);
                break;
            case '3':
                // affichage de la regle du jeu
                regleDuJeu();
                break;
            case '4':
                // genere un egrille
                //generateur(grille);
                break;
            case '5':
                // affiche un egrille
                afficheGrille(grille);
                break;
            case '6':
                // affiche la grille initiale
                afficheGrilleInitiale();
                break;
            case '9':
                // quitte le jeu
                printf("fin de partie\n");
                break;
            default:
                printf("ERREUR : valeur Erronée\n");
                break;
        }
    }

    // liberation de la mémoire allouée
    grilleDelete(grille);
}