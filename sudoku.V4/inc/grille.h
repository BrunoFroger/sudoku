//
//      grille.h
//


extern char grilleInitiale[81];
extern int lastLigne;
extern int lastColonne;

char **grilleNew(void);
int grilleDelete(char **grille);
int grilleResetAll(char **grille);
int grilleLoadInitiale(char **grille);
void initGrilleInitiale(void);
int grilleSetValeur(char **grille, int ligne, int colonne, char valeur);
int grilleResetValeur(char **grille, int ligne, int colonne);
int grilleTestValeur(char **grille, int ligne, int colonne, char valeur);
int grilleTestLigneValide(char **grille, int ligne);
int grilleTestColonneValide(char **grille, int colonne);
int grilleTestRegionValide(char **grille, int ligneRegion, int clonneRegion);
int testListeValide(char *liste);
