//
//      test.c
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../inc/testJeu.h"
#include "../inc/lireFichier.h"
#include "../inc/afficheGrille.h"
#include "../inc/grille.h"
#include "../inc/solve.h"

int numTest = 0;
int nbTestsOK = 0;
int nbTestsKO = 0;
int nbTestsNA = 0;
int nbTestsExec = 0;
char nomFonction[50];
char nomTest[200];
int stopOnErreur = 0;
int testToExecute[100];
int idxTestToExecute=0;

//--------------------------------------------------------
//
//          E R R E U R
//
//--------------------------------------------------------
void testErreur(char *message){
    printf("ERREUR => test %2d -> dans la fonction %s : %s\n", numTest, nomFonction, message);
    nbTestsKO++;
    if (stopOnErreur != 0) exit(0);
}

//--------------------------------------------------------
//
//          T E S T O K
//
//--------------------------------------------------------
void testOk(void){
    printf("test %2d OK -> fonction %s\n", numTest, nomTest);
    nbTestsOK++;
}

//--------------------------------------------------------
//
//          T E S T B I L A N
//
//--------------------------------------------------------
void testBilan(void){
    int tauxReussite;
    if (nbTestsOK == 0){
        tauxReussite = 0;
    } else {
        tauxReussite = nbTestsOK * 100 / nbTestsExec;
    }
    if ((nbTestsKO + nbTestsOK) != nbTestsExec){
        printf("ERREUR : le bilan des tests ne peut pas etre calcule !\n");
        printf("la somme du nombre d etests OK et KO ne correspond pas au nombre total de tests\n");
        printf(" nb total de tests : %d\n", numTest);
        printf(" nb tests  exec    : %d\n", nbTestsExec);
        printf(" nb tests  OK      : %d\n", nbTestsOK);
        printf(" nb tests  KO      : %d\n", nbTestsKO);
        printf(" nb tests  NA      : %d\n", nbTestsNA);
    } else {
        printf("+----------------------+\n");
        printf("|    bilan des tests   |\n");
        printf("+----------------------+\n");
        printf("|  nb tests  |    %2d   |\n", numTest);
        printf("|  nb NA     |    %2d   |\n", nbTestsNA);
        printf("|  nb exec   |    %2d   |\n", nbTestsExec);
        printf("+----------------------+\n");
        printf("|  tests OK  |    %2d   |\n", nbTestsOK);
        printf("|  tests KO  |    %2d   |\n", nbTestsKO);
        printf("| %% reussite |   %3d%%  |\n", tauxReussite);
        printf("+----------------------+\n");
    }
}

//--------------------------------------------------------
//
//          T E S T N E W
//
//--------------------------------------------------------
bool testNew(char *fonction, char *nom){

    numTest++;
    if (idxTestToExecute > 0){
        for (int i = 0 ; i < idxTestToExecute ; i++){
            if (numTest == testToExecute[i]){
                printf("-------------------------------------------------\n");
                printf("nouveau Test (%d) : %s\n", numTest, nom);
                strcpy(nomTest, nom);
                strcpy(nomFonction, fonction);
                nbTestsExec++;
                return true;
            } 
        }    
    } else {
        printf("-------------------------------------------------\n");
        printf("nouveau Test (%d) : %s\n", numTest, nom);
        strcpy(nomTest, nom);
        strcpy(nomFonction, fonction);
        nbTestsExec++;
        return true;
    }

    nbTestsNA++;
    return false;
}

//--------------------------------------------------------
//
//          M A I N
//
//--------------------------------------------------------
int main(int argc, char **argv){
    char **grille;
    char parametre[25];

    // test si des parametres 
    if (argc > 1){
        for (int i = 1 ; i < argc ; i++){
            strcpy(parametre, argv[i]);
            printf("Analyse du parametre %d : %s\n", i, parametre);
            if (strcmp(parametre,"aide") == 0){
                // affichage de l'aide
                printf("parametres disponibles :\n");
                printf("  aide : cette aide\n");
                printf("  test xx : execution du test numero xx\n");
            } else if (strcmp(parametre, "test") == 0){
                // execution de tests spéciifiés
                char numTestChar[10];
                while (i <= (argc - 2)){
                    printf("test du parametre %d\n", i);
                    strcpy(numTestChar,argv[++i]);
                    int monTest = atoi(numTestChar);
                    testToExecute[idxTestToExecute++] = monTest;
                    printf("Execution du test %s(%d)\n", numTestChar, monTest);
                }
                printf("liste des tests a executer :");
                for (int i = 0 ; i < idxTestToExecute ; i++){
                    printf("%d, ",testToExecute[i]);
                }
                printf("\n");
                break;
            } else if (strcmp(parametre, "stopOnError") == 0){
                stopOnErreur = 1 ;
            } else if (strcmp(parametre, "") == 0){
                // 
            } else {
                // commande inconnue
                printf("parametre %s inconnu\n", parametre);
                printf(" parametre aide pour connaitre les options posssibles\n"); 
                exit(-1);
            }
        }
    }

    //exit(0);

    printf("=================================================\n");
    printf("Tests du programme Sudoku\n");

    grille = grilleNew();
    if (testNew("grilleNew", "creation d'une grille vide")){
        if (grille == NULL){
            testErreur("erreur creation d'une grille");
        } else {
            testOk();
        }
    }

    if (testNew("afficheGrille", "test d'affichage de la grille vide")){
        afficheGrille(grille);
        testOk();
    }

    if (testNew("lireFichier", "lecture de fichier valide")){
        char nomFichier[50] = "modeles/grilleFacile";
        //char nomFichier[50] = "../grilles/bruno";
        //char nomFichier[50] = "bruno";
        if (lireFichier(nomFichier, grille) == 0){
            testErreur("erreur ouverture fichier valide");
        } else {
            testOk();
        }
    }

    if (testNew("afficheGrille", "test d'affichage de la grille valide avant recherche de solution")){
        afficheGrille(grille);
        testOk();
    }

    if (testNew("solve", "recherche d'une solution d'un fichier valide")){
        int resultat = solve(grille, 1);
        if (resultat != 1){
            char tmpChaine[250];
            sprintf(tmpChaine,"erreur pas de solution trouvee pour une grille valide nbSolutions = %d",resultat);
            testErreur(tmpChaine);
        } else {
            testOk();
        }
    }

    if (testNew("lireFichier", "lecture de fichier valide")){
        if (lireFichier("../grilles/bruno", grille) == 0){
            testErreur("erreur ouverture fichier valide");
        } else {
            testOk();
        }
    }

    if (testNew("lireFichier", "lecture de fichier invalide")){
        if (lireFichier("../grilles/brunozzz", grille) == 1){
            testErreur("erreur ouverture fichier invalide");
        } else {
            testOk();
        }
    }

    if (testNew("afficheGrille", "affichage de la grille remplie")){
        afficheGrille(grille);
        testOk();
    }

    if (testNew("testJeu", "fonction de test de jeu (1,1,'1',0) invalide")){
        if (testJeu(grille,1,1,'1',0) == 1){
            testErreur("la valeur qui existe deja dans la ligne n'est pas detectee");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (1,1,'2',0) valide")){
        if (testJeu(grille,1,1,'2',0) == 0){
            testErreur("test valide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (1,1,'1',1) invalide")){
        if (testJeu(grille,1,1,'1',1) == 1){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (0,1,'1',1) avec numero de ligne invalide")){
        if (testJeu(grille,0,1,'1',1) == 1){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (10,1,'1',1) avec numero de ligne invalide")){
        if (testJeu(grille,10,1,'1',1) == 1){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (1,0,'1',1) avec numero de colonne invalide")){
        if (testJeu(grille,1,0,'1',1) == 1){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (1,10,'1',1) avec numero de colonne invalide")){
        if (testJeu(grille,1,10,'1',1) == 1){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    char **grilleTest = grilleNew();
    if (testNew("grilleNew", "tests de la fonction de creation d'une grille")){
        if (grilleTest == NULL){
            testErreur("impossible de creer une nouvelle grille");
        } else {
            testOk();
        }
    }

    if (testNew("grilleDelete", "tests de la fonction de destruction d'une grille")){
        if (grilleDelete(grilleTest) == -1){
            testErreur("impossible de creer une nouvelle grille");
        } else {
            testOk();
        }
    }

    if (testNew("testListeValide", "tests unicite dans une liste de 9 valeurs valide")){
        char listeValeurValide[9]={'1','2','3','4','5','6','7','8','9'};
        if (testListeValide(listeValeurValide) == -1){
            testErreur("erreur calcul unicite liste de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("testListeValide", "tests unicite dans une liste de 9 valeurs invalide")){
        char listeValeurInvalide[9]={'1','2','3','4','1','6','7','8','9'};
        if (testListeValide(listeValeurInvalide) == 0){
            testErreur("erreur calcul unicite liste de valeurs invalide");
        } else {
            testOk();
        }
    }

    if (testNew("testListeValide", "tests unicite dans une liste de 9 valeurs incomplete")){
        char listeValeurIncomplete[9]={'1',' ','3','4',' ','6','7','8','9'};
        if (testListeValide(listeValeurIncomplete) != 0){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestLigneValide", "test validité ligne (0) de 9 valeurs incomplete")){
        if (grilleTestLigneValide(grille,0) != 0){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }
    
    if (testNew("grilleTestLigneValide", "test validité ligne (6) de 9 valeurs incomplete")){
        if (grilleTestLigneValide(grille,6) != 0){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }
    
    if (testNew("grilleTestColonneValide", "test validité colonne (0) de 9 valeurs incomplete")){
        if (grilleTestColonneValide(grille,0) != 0){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }
    
    if (testNew("grilleTestColonneValide", "test validité colonne (6) de 9 valeurs incomplete")){
        if (grilleTestColonneValide(grille,6) != 0){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (0,0) de 9 valeurs incomplete")){
        if (grilleTestRegionValide(grille,0,0) != 0){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (1,2) de 9 valeurs incomplete")){
        if (grilleTestRegionValide(grille,1,2) != 0){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (2,2) de 9 valeurs incomplete")){
        if (grilleTestRegionValide(grille,2,2) != 0){
            testErreur("erreur calcul region (2,2) incomplete valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (0,0) de 9 valeurs complete")){
        lireFichier("bruno",grille);
        grilleSetValeur(grille,0,0,'2');
        grilleSetValeur(grille,0,1,'4');
        grilleSetValeur(grille,1,1,'7');
        grilleSetValeur(grille,1,2,'6');
        grilleSetValeur(grille,2,1,'5');
        grilleSetValeur(grille,2,2,'8');
        //afficheGrille(grille);
        if (grilleTestRegionValide(grille,0,0) != 0){
            testErreur("erreur calcul region complete valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (0,0) de 9 valeurs complete invalide")){
        lireFichier("bruno",grille);
        grilleSetValeur(grille,0,0,'2');
        grilleSetValeur(grille,0,1,'4');
        grilleSetValeur(grille,1,1,'7');
        grilleSetValeur(grille,1,2,'6');
        grilleSetValeur(grille,2,1,'1');
        grilleSetValeur(grille,2,2,'8');
        //afficheGrille(grille);
        if (grilleTestRegionValide(grille,0,0) == 0){
            testErreur("erreur calcul region complete invalide");
        } else {
            testOk();
        }
    }

    printf("-------------------------------------------------\n");
    testBilan();
    //getchar();
}