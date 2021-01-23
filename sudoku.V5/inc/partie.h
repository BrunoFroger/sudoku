//
//      partie.h
//

#ifndef __PARTIE
#define __PARTIE

#include <stdbool.h>

extern bool chargePartie(char **grille);
extern void jouePartie(char **grille);
extern bool testJeu(char **grille, int ligne, int colonne, char valeur, bool silence);

#endif