//
//      test.c
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../inc/grille.h"
#include "../inc/fichiers.h"
#include "../inc/partie.h"
#include "../inc/generateur.h"
#include "../inc/solve.h"

int numTest = 0;
int nbTestsOK = 0;
int nbTestsKO = 0;
int nbTestsNA = 0;
int nbTestsExec = 0;
char nomFonction[50];
char nomTest[200];
bool modePasAPas = false;
int stopOnErreur = 0;
int testToExecute[100];
int idxTestToExecute=0;
bool blocExecute;

//--------------------------------------------------------
//
//          E R R E U R
//
//--------------------------------------------------------
void testErreur(char *message){
    printf("ERREUR => test %2d -> dans la fonction %s : %s\n", numTest, nomFonction, message);
    nbTestsKO++;
    if (stopOnErreur != 0) exit(0);
    if (modePasAPas){
        printf("Fin de test => appuyez sur entree pour continuer : ");
        getchar();
    }
}

//--------------------------------------------------------
//
//          T E S T O K
//
//--------------------------------------------------------
void testOk(void){
    printf("test %2d OK -> fonction %s\n", numTest, nomTest);
    nbTestsOK++;
    if (modePasAPas){
        printf("Fin d'un bloc de tests => appuyez sur entree pour continuer");
        getchar();
    }
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
//          S E T T E S T
//
//--------------------------------------------------------
bool setTest(char *fonction, char *nom, bool execute){
    printf("-------------------------------------------------\n");
    printf("nouveau Test (%d) : %s\n", numTest, nom);
    strcpy(nomTest, nom);
    strcpy(nomFonction, fonction);
    if (execute){
        nbTestsExec++;
        return true;
    } else {
        printf("Test non execute (NA)\n");
        nbTestsNA++;
        return false;
    }
}

//--------------------------------------------------------
//
//          T E S T N E W
//
//--------------------------------------------------------
bool testNew(char *fonction, char *nom, bool execute){
    numTest++;
    if (idxTestToExecute > 0){
        for (int i = 0 ; i < idxTestToExecute ; i++){
            if (numTest == testToExecute[i]){
                return setTest(fonction, nom, execute);
            } 
        }    
    } else {
        return setTest(fonction, nom, execute);
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
    char **grille = NULL;
    char parametre[25];

    //--------------------------------------------------------
    //
    //              test si des parametres 
    //
    //--------------------------------------------------------
    if (argc > 1){
        for (int i = 1 ; i < argc ; i++){
            strcpy(parametre, argv[i]);
            printf("Analyse du parametre %d : %s\n", i, parametre);
            if (strcmp(parametre,"aide") == 0){
                // affichage de l'aide
                printf("parametres disponibles :\n");
                printf("  aide : cette aide\n");
                printf("  test xx : execution du test numero xx\n");
                printf("  pap     : mode pas a pas, pause apres chaque test\n");
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
            } else if (strcmp(parametre, "pap") == 0){
                modePasAPas = true ;
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

    //--------------------------------------------------------
    //--------------------------------------------------------
    //--------------------------------------------------------
    //
    //
    //          Debut des tests
    //
    //
    //--------------------------------------------------------
    //--------------------------------------------------------
    //--------------------------------------------------------
    printf("=================================================\n");
    printf("Tests du programme Sudoku\n");

    //--------------------------------------------------------
    //
    //          tests creation/suppression de grille
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("grilleDelete", "suppression d'une grille qui n'existe pas", blocExecute)){
        if (grilleDelete(grille) != false){
            testErreur("erreur suppression d'une grille qui existe");
        } else {
            testOk();
        }
    }

    grille = grilleNew();
    if (testNew("grilleNew", "creation d'une grille vide", blocExecute)){
        if (grille == NULL){
            testErreur("erreur creation d'une grille");
        } else {
            testOk();
        }
    }

    if (testNew("grilleDelete", "suppression d'une grille qui existe", blocExecute)){
        if (grilleDelete(grille) != true){
            testErreur("erreur suppression d'une grille qui existe");
        } else {
            testOk();
        }
    }

    if (testNew("grilleNew", "verification des valeurs initiales d'une nouvelle grille", blocExecute)){
        bool resultat = true;
        char ** grilleTmp = grilleNew();
        for (int lig = 0 ; lig < TAILLEGRILLE ; lig ++){
            for (int col = 0 ; col < TAILLEGRILLE ; col++){
                if (grilleTmp[lig][col] != ' ') resultat = false;
            }
        }
        if (!resultat){
            testErreur("erreur la grile ne contient pas que des ' '");
        } else {
            testOk();
        }
        grilleDelete(grilleTmp);
    }
    grille = grilleNew();
    
    //--------------------------------------------------------
    //
    //          tests lecture / ecriture de grilles
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("lireFichier", "lecture de fichier modele valide", blocExecute)){
        char nomFichier[50] = "../grilles/modeles/grilleFacile";
        if (lireFichier(nomFichier, grille) == false){
            testErreur("erreur ouverture fichier valide");
        } else {
            testOk();
        }
    }

    if (testNew("lireFichier", "lecture de fichier valide", blocExecute)){
        if (lireFichier("../grilles/bruno", grille) == false){
            testErreur("erreur ouverture fichier valide");
        } else {
            testOk();
        }
    }

    if (testNew("lireFichier", "lecture de fichier invalide", blocExecute)){
        if (lireFichier("../grilles/brunozzz", grille) == true){
            testErreur("erreur on a reussi a ouvrir un fichier invalide");
        } else {
            testOk();
        }
    }
    
    //--------------------------------------------------------
    //
    //          tests grille pleine ou non pleine
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("grillePleine", "test grille pleine sur grille non pleine", blocExecute)){
        lireFichier("../grilles/modele/facile", grille);
        if (grillePleine(grille) == false){
            testOk();
        } else {
            testErreur("erreur grille non pleine");
        }
    }

    if (testNew("grillePleine", "test grille pleine sur grille pleine", blocExecute)){
        if (lireFichier("../grilles/modeles/grillepleine", grille) != false){
            if (grillePleine(grille) == true){
                testOk();
            } else {
                testErreur("erreur grille pleine non detectee");
            }
        } else {
            testErreur("erreur fichier grille pleine non trouvee");
        }
    }
    
    //--------------------------------------------------------
    //
    //          tests set/reset valeurs
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("grilleSetValeur", "test set valeur dans une case vide", blocExecute)){
        char **grille = grilleNew();
        initGrilleInitiale();
        if (grilleSetValeur(grille, 0 ,0, '1') == false){
            testErreur("erreur imposible de modifier cette case");
        } else {
            testOk();
        }
    }
    
    if (testNew("grilleSetValeur", "test set valeur dans une case non vide", blocExecute)){
        char **grille = grilleNew();
        initGrilleInitiale();
        if (lireFichier("../grilles/modeles/grillepleine", grille) != false){
            if (grilleSetValeur(grille, 0 ,0, '1') == false){
                testOk();
            } else {
                testErreur("erreur imposible de modifier cette case");
            }
        } else {
            testErreur("erreur fichier grille pleine non trouvee");
        }
    }
    
    if (testNew("grilleSetValeur", "test reset valeur dans une case autorisee", blocExecute)){
        char **grille = grilleNew();
        initGrilleInitiale();
        if (lireFichier("../grilles/modeles/grilleFacile", grille) != false){
            grilleSetValeur(grille, 0 ,0, '1');
            if (grilleSetValeur(grille, 0 ,0, '2') == true){
                testOk();
            } else {
                testErreur("erreur imposible de modifier cette case");
            }
        } else {
            testErreur("erreur fichier grille pleine non trouvee");
        }
    }
    
    if (testNew("grilleSetValeur", "test reset valeur dans une case autorisee", blocExecute)){
        char **grille = grilleNew();
        initGrilleInitiale();
        if (lireFichier("../grilles/modeles/grilleFacile", grille) != false){
            grilleSetValeur(grille, 0 ,0, '1');
            if (grilleResetValeur(grille, 0 ,0) == true){
                testOk();
            } else {
                testErreur("erreur imposible de modifier cette case");
            }
        } else {
            testErreur("erreur fichier grille pleine non trouvee");
        }
    }
    
    //--------------------------------------------------------
    //
    //          tests validite de grille
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("grilleValide", "test grille valide sur grille vide", blocExecute)){
        char **grilleTmp = grilleNew();
        if (grilleValide(grilleTmp,false) == false){
            testErreur("erreur grille vide consideree comme non valide");
        } else {
            testOk();
        }
        grilleDelete(grilleTmp);
    }

    if (testNew("grilleValide", "test grille valide sur grille facile", blocExecute)){
        char **grilleTmp = grilleNew();
        if (lireFichier("../grilles/modeles/grilleFacile",grilleTmp) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else {
            if (grilleValide(grilleTmp,false) == false){
                testErreur("erreur grille vide consideree comme non valide");
            } else {
                testOk();
            }
        }
        grilleDelete(grilleTmp);
    }

    if (testNew("grilleValide", "test grille valide sur grille pleine", blocExecute)){
        char **grilleTmp = grilleNew();
        if (lireFichier("../grilles/modeles/grillePleine",grilleTmp) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else {
            if (grilleValide(grilleTmp,false) == false){
                testErreur("erreur grille vide consideree comme non valide");
            } else {
                testOk();
            }
        }
        grilleDelete(grilleTmp);
    }

    if (testNew("grilleValide", "test grille avec ligne incorrecte sur grille facile", blocExecute)){
        char **grilleTmp = grilleNew();
        if (lireFichier("../grilles/modeles/grilleFacile",grilleTmp) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else {
            grilleSetValeur(grilleTmp, 0, 0, '1');
            //afficheGrille(grilleTmp);
            if (grilleValide(grilleTmp,false) != false){
                testErreur("erreur grille vide consideree comme non valide");
            } else {
                testOk();
            }
        }
        grilleDelete(grilleTmp);
    }
    
    if (testNew("grilleValide", "test grille avec colonne incorrecte sur grille facile", blocExecute)){
        char **grilleTmp = grilleNew();
        if (lireFichier("../grilles/modeles/grilleFacile",grilleTmp) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else {
            grilleSetValeur(grilleTmp, 0, 0, '6');
            //afficheGrille(grilleTmp);
            if (grilleValide(grilleTmp,false) != false){
                testErreur("erreur grille vide consideree comme non valide");
            } else {
                testOk();
            }
        }
        grilleDelete(grilleTmp);
    }
        
    if (testNew("grilleValide", "test grille avec region incorrecte sur grille facile", blocExecute)){
        char **grilleTmp = grilleNew();
        if (lireFichier("../grilles/modeles/grilleFacile",grilleTmp) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else {
            grilleSetValeur(grilleTmp, 5, 1, '3');
            //afficheGrille(grilleTmp);
            if (grilleValide(grilleTmp,false) != false){
                testErreur("erreur grille vide consideree comme non valide");
            } else {
                testOk();
            }
        }
        grilleDelete(grilleTmp);
    }
    
    //--------------------------------------------------------
    //
    //          tests comparaison de grilles
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("compareGrille", "test comparaison de grilles identiques", blocExecute)){
        char **grille1 = grilleNew();
        char **grille2 = grilleNew();
        if (lireFichier("../grilles/modeles/grilleFacile",grille1) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else if (lireFichier("../grilles/modeles/grilleFacile",grille2) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else {
            if (compareGrille(grille1, grille2) == false){
                testErreur("erreur comparaison de grille identique invaide");
            } else {
                testOk();
            }
        }
        grilleDelete(grille1);
        grilleDelete(grille2);
    }

    if (testNew("compareGrille", "test comparaison de grilles differentes", blocExecute)){
        char **grille1 = grilleNew();
        char **grille2 = grilleNew();
        if (lireFichier("../grilles/modeles/grilleFacile",grille1) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else if (lireFichier("../grilles/modeles/grilleExpert",grille2) == false){
            testErreur("erreur impossible ouvrir fichier grilleExpert");
        } else {
            if (compareGrille(grille1, grille2) != false){
                testErreur("erreur comparaison de grille differentes invaide");
            } else {
                testOk();
            }
        }
        grilleDelete(grille1);
        grilleDelete(grille2);
    }
    
    //--------------------------------------------------------
    //
    //          tests copie de grille
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("copieGrile", "test copie de grilles", blocExecute)){
        char **grilleOrigine = grilleNew();
        char **grilleDestination = grilleNew();
        if (lireFichier("../grilles/modeles/grilleFacile",grilleOrigine) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else if (lireFichier("../grilles/modeles/grilleFacile",grilleDestination) == false){
            testErreur("erreur impossible ouvrir fichier grilleFacile");
        } else {
            copieGrille(grilleOrigine,grilleDestination);
            if (compareGrille(grilleOrigine, grilleDestination) == false){
                testErreur("erreur copie de grille invaide");
            } else {
                testOk();
            }
        }
        grilleDelete(grilleOrigine);
        grilleDelete(grilleDestination);
    }

    //--------------------------------------------------------
    //
    //          tests listes
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("testListeValide", "tests unicite dans une liste de 9 valeurs valide", blocExecute)){
        char listeValeurValide[9]={'1','2','3','4','5','6','7','8','9'};
        if (testListeValide(listeValeurValide) == false){
            testErreur("erreur calcul unicite liste de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("testListeValide", "tests unicite dans une liste de 9 valeurs invalide", blocExecute)){
        char listeValeurInvalide[9]={'1','2','3','4','1','6','7','8','9'};
        if (testListeValide(listeValeurInvalide) == true){
            testErreur("erreur calcul unicite liste de valeurs invalide");
        } else {
            testOk();
        }
    }

    if (testNew("testListeValide", "tests unicite dans une liste de 9 valeurs incomplete", blocExecute)){
        char listeValeurIncomplete[9]={'1',' ','3','4',' ','6','7','8','9'};
        if (testListeValide(listeValeurIncomplete) != true){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestLigneValide", "test validité ligne (0) de 9 valeurs incomplete", blocExecute)){
        if (grilleTestLigneValide(grille,0) != true){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }
    
    if (testNew("grilleTestLigneValide", "test validité ligne (6) de 9 valeurs incomplete", blocExecute)){
        if (grilleTestLigneValide(grille,6) != true){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }
    
    if (testNew("grilleTestColonneValide", "test validité colonne (0) de 9 valeurs incomplete", blocExecute)){
        if (grilleTestColonneValide(grille,0) != true){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }
    
    if (testNew("grilleTestColonneValide", "test validité colonne (6) de 9 valeurs incomplete", blocExecute)){
        if (grilleTestColonneValide(grille,6) != true){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (0,0) de 9 valeurs incomplete", blocExecute)){
        if (grilleTestRegionValide(grille,0,0) != true){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (1,2) de 9 valeurs incomplete", blocExecute)){
        if (grilleTestRegionValide(grille,1,2) != true){
            testErreur("erreur calcul unicite liste incomplete de valeurs valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (2,2) de 9 valeurs incomplete", blocExecute)){
        if (grilleTestRegionValide(grille,2,2) != true){
            testErreur("erreur calcul region (2,2) incomplete valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (0,0) de 9 valeurs complete", blocExecute)){
        lireFichier("bruno",grille);
        grilleSetValeur(grille,0,0,'2');
        grilleSetValeur(grille,0,1,'4');
        grilleSetValeur(grille,1,1,'7');
        grilleSetValeur(grille,1,2,'6');
        grilleSetValeur(grille,2,1,'5');
        grilleSetValeur(grille,2,2,'8');
        //afficheGrille(grille);
        if (grilleTestRegionValide(grille,0,0) != true){
            testErreur("erreur calcul region complete valide");
        } else {
            testOk();
        }
    }

    if (testNew("grilleTestRegionValide", "test validité region (0,0) de 9 valeurs complete invalide", blocExecute)){
        lireFichier("bruno",grille);
        grilleSetValeur(grille,0,0,'2');
        grilleSetValeur(grille,0,1,'4');
        grilleSetValeur(grille,1,1,'7');
        grilleSetValeur(grille,1,2,'6');
        grilleSetValeur(grille,2,1,'1');
        grilleSetValeur(grille,2,2,'8');
        //afficheGrille(grille);
        if (grilleTestRegionValide(grille,0,0) == true){
            testErreur("erreur calcul region complete invalide");
        } else {
            testOk();
        }
    }

    //--------------------------------------------------------
    //
    //          tests fonction testJeu
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("testJeu", "fonction de test de jeu (0,0,'1',0) invalide", blocExecute)){
        lireFichier("../grilles/bruno",grille);
        if (testJeu(grille,0,0,'1',0) == true){
            testErreur("la valeur qui existe deja dans la ligne n'est pas detectee");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (0,0,'2',0) valide", blocExecute)){
        if (testJeu(grille,0,0,'2',0) == false){
            testErreur("test valide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (0,0,'1',1) invalide", blocExecute)){
        if (testJeu(grille,0,0,'1',1) == true){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (-1,0,'1',1) avec numero de ligne invalide", blocExecute)){
        if (testJeu(grille,-1,0,'1',1) == true){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (9,0,'1',1) avec numero de ligne invalide", blocExecute)){
        if (testJeu(grille,9,0,'1',1) == true){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (0,-1,'1',1) avec numero de colonne invalide", blocExecute)){
        if (testJeu(grille,0,-1,'1',1) == true){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de la fonction de test de jeu (0,9,'1',1) avec numero de colonne invalide", blocExecute)){
        if (testJeu(grille,0,9,'1',1) == true){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests d'ecriture sur une case de la grille initiale (0,2,'7',1) ", blocExecute)){
        lireFichier("../grilles/bruno",grille);
        if (testJeu(grille,0,2,'7',1) == true){
            testErreur("test invalide NOK");
        } else {
            testOk();
        }
    }

    if (testNew("testJeu", "tests de modification d'une case (0,0,'2',1) puis (0,0,'4',1)", blocExecute)){
        lireFichier("../grilles/bruno",grille);
        if (testJeu(grille,0,0,'7',1) == true){
            if (testJeu(grille,0,0,'4',1) == true){
                testOk();
            } else {
                testErreur("test invalide NOK");
            }
        } else {
            testErreur("test invalide NOK");
        }
    }

    if (testNew("testJeu", "tests jeu derniere valeur grille complete (8,8,'4',1)", blocExecute)){
        lireFichier("../grilles/modeles/grillePresquePleine",grille);
        if (testJeu(grille,8,8,'4',1) == true){
            grilleSetValeur(grille,8,8,'4');
            if (grillePleine(grille) == true){
                testOk();
            } else {
                testErreur("test invalide NOK : grille non pleine");
            }
        } else {
            testErreur("test invalide NOK : jeu invalide");
        }
    }

    //--------------------------------------------------------
    //
    //          fonction solve
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("solve", "tests resolution d'une grille valide manque 1 valeur", blocExecute)){
        lireFichier("../grilles/modeles/grillePresquePleine",grille);
        int nbSolutions = solve(grille, true);
        printf("Nombre de solutions trouvées = %d\n\n", nbSolutions);
        if (nbSolutions >= 1){
            if (grillePleine(grille)){
                testOk();
            } else {
                testErreur("test NOK : la grille n'est pas finie");
            }
        } else {
            testErreur("test NOK : solve n'a pas de solution");
        }
    }

    if (testNew("solve", "tests resolution d'une grille valide manque 2 valeurs", blocExecute)){
        lireFichier("../grilles/modeles/grillePresquePleine1",grille);
        int nbSolutions = solve(grille, true);
        printf("Nombre de solutions trouvées = %d\n\n", nbSolutions);
        if (nbSolutions >= 1){
            if (grillePleine(grille)){
                testOk();
            } else {
                testErreur("test NOK : la grille n'est pas finie");
            }
        } else {
            testErreur("test NOK : solve n'a pas de solution");
        }
    }

    if (testNew("solve", "tests resolution d'une grille valide manque 3 valeurs", blocExecute)){
        lireFichier("../grilles/modeles/grillePresquePleine2",grille);
        int nbSolutions = solve(grille, true);
        printf("Nombre de solutions trouvées = %d\n\n", nbSolutions);
        if (nbSolutions >= 1){
            if (grillePleine(grille)){
                testOk();
            } else {
                testErreur("test NOK : la grille n'est pas finie");
            }
        } else {
            testErreur("test NOK : solve n'a pas de solution");
        }
    }

    if (testNew("solve", "tests resolution d'une grille facile", blocExecute)){
        lireFichier("../grilles/modeles/grilleFacile",grille);
        int nbSolutions = solve(grille, true);
        printf("Nombre de solutions trouvées = %d\n\n", nbSolutions);
        if (nbSolutions >= 1){
            if (grillePleine(grille)){
                testOk();
            } else {
                testErreur("test NOK : la grille n'est pas finie");
            }
        } else {
            testErreur("test NOK : solve n'a pas de solution");
        }
    }

    if (testNew("solve", "tests resolution d'une grille intermediaire", blocExecute)){
        lireFichier("../grilles/modeles/grilleIntermediaire",grille);
        int nbSolutions = solve(grille, true);
        printf("Nombre de solutions trouvées = %d\n\n", nbSolutions);
        if (nbSolutions >= 1){
            if (grillePleine(grille)){
                testOk();
            } else {
                testErreur("test NOK : la grille n'est pas finie");
            }
        } else {
            testErreur("test NOK : solve n'a pas de solution");
        }
    }

    if (testNew("solve", "tests resolution d'une grille difficile", blocExecute)){
        lireFichier("../grilles/modeles/grilleExpert",grille);
        int nbSolutions = solve(grille, false);
        printf("Nombre de solutions trouvées = %d\n\n", nbSolutions);
        if (nbSolutions >= 1){
            if (grillePleine(grille)){
                testOk();
            } else {
                testErreur("test NOK : la grille n'est pas finie");
            }
        } else {
            testErreur("test NOK : solve n'a pas de solution");
        }
    }

    //--------------------------------------------------------
    //
    //          generateur
    //
    //--------------------------------------------------------
    blocExecute = true;
    if (testNew("generateur", "tests generation de liste de valeur", blocExecute)){
        char liste[9];
        initGenerateur(grille);
        genereListeValeur(liste);
        if (testListeValide(liste) == true){
            testOk();
        } else {
            testErreur("test NOK : liste generee invalide");
        }
    }
    
    if (testNew("generateur", "tests generation 1000 nombres aléatoires", blocExecute)){
        initGenerateur(grille);
        bool testAleatoireOK = true;
        for (int i = 0 ; i < 1000 ; i++){
            int valeur = getRandomValue();
            if ((valeur < 0) || (valeur > 8)){
                testAleatoireOK = false;
                printf("nombre genere NOK = %d\n", valeur);
            }
        }
        if (testAleatoireOK){
            testOk();
        } else {
            testErreur("test NOK : nombre aléatoire genere invalide");
        }
    }
    
    if (testNew("generateur", "tests generation liste 9 valeurs differentes", blocExecute)){
        initGenerateur(grille);
        char listeValeurs[9];
        genereListeValeur(listeValeurs);
        if (testListeValide(listeValeurs)){
            testOk();
        } else {
            testErreur("test NOK : liste nombres aléatoire genere invalide");
        }
    }

    if (testNew("generateur", "tests generation d'une grille", false)){
        initGenerateur(grille);
        char **grille = grilleNew();
        if (generateur(grille)){
            testOk();
        } else {
            testErreur("test NOK : generation d'une grille invalide");
        }
    }

    printf("-------------------------------------------------\n");
    testBilan();
    //getchar();
}