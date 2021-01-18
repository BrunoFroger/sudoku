//
//      afficheGrille.c
//



#include <stdio.h>



//--------------------------------------------------------
//
//         A F F I C H E G R I L L E
//
//--------------------------------------------------------
void afficheGrille(char **grille){
    printf("\n");
    printf("    1   2   3    4   5   6    7   8   9\n");
    printf("  +---+---+---++---+---+---++---+---+---+\n");
    for (int ligne = 0 ; ligne < 9 ; ligne++){
        printf("%d |", ligne + 1);
        for (int colonne = 0 ; colonne < 9 ; colonne++){
            printf(" %c |",grille[ligne][colonne]);
            if ((colonne == 2) || (colonne == 5)) printf("|");
        }
        printf("\n");
        printf("  +---+---+---++---+---+---++---+---+---+\n");
        if ((ligne == 2) || (ligne == 5)) printf("  +---+---+---++---+---+---++---+---+---+\n");
    }
}
