//
//      grille.h
//


#ifndef __GRILLE
#define __GRILLE

#include <stdbool.h>

#define TAILLEGRILLE    9
#define NBLIGNES        TAILLEGRILLE
#define NBCOLONNES      TAILLEGRILLE

extern char grilleInitiale[TAILLEGRILLE][TAILLEGRILLE];
extern int lastLigne;
extern int lastColonne;

extern char **grilleNew(void);
extern bool grilleDelete(char **grille);
extern bool grilleResetAll(char **grille);
extern bool grilleLoadInitiale(char **grille);
extern bool grilleSetInitiale(char **grille);
extern void initGrilleInitiale(void);
extern bool grilleSetValeur(char **grille, int ligne, int colonne, char valeur);
extern bool grilleResetValeur(char **grille, int ligne, int colonne);
extern bool grilleTestValeur(char **grille, int ligne, int colonne, char valeur);
extern bool grilleTestLigneValide(char **grille, int ligne);
extern bool grilleTestColonneValide(char **grille, int colonne);
extern bool grilleTestRegionValide(char **grille, int ligneRegion, int clonneRegion);
extern bool testListeValide(char *liste);
extern bool grillePleine(char **grille);
extern bool grilleValide(char **grille);
extern void afficheGrille(char **grille);
extern bool compareGrille(char **grille1, char **grille2);
extern void copieGrille(char **grilleOrigine, char **grilleDestination);
extern void afficheGrilleInitiale(void);

#endif
