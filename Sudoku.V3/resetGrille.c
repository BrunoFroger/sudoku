//
//      resetGrille.c
//

#include "lireFichier.h"

//--------------------------------------------------------
//
//          R E S E T G R I L L E
//
//--------------------------------------------------------
void resetGrille(char **grille){
    for (int lig = 0 ; lig < 9 ; lig++){
        for (int col = 0 ; col < 9 ; col++){
            grille[lig][col] = grilleInitiale[lig*9+col];
        }
    }
}