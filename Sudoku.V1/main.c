//
//  Sudoku.c
//

#include <stdio.h>

// definition des constantes
char partieFacile[9][9] = 
    {
        {' ', ' ', '1',     ' ', ' ', '3',      '8', '9', ' '},
        {'9', ' ', ' ',     '8', ' ', ' ',      ' ', ' ', ' '},
        {'3', ' ', ' ',     ' ', '9', ' ',      ' ', ' ', '6'},

        {'8', ' ', ' ',     ' ', '4', ' ',      ' ', '5', ' '},
        {' ', ' ', '3',     '9', ' ', '1',      '6', ' ', ' '},
        {'1', ' ', ' ',     ' ', '8', ' ',      ' ', ' ', '2'},
        
        {'6', ' ', ' ',     ' ', '1', ' ',      ' ', ' ', '7'},
        {' ', ' ', ' ',     ' ', ' ', '6',      ' ', ' ', '5'},
        {' ', '2', '5',     '7', ' ', ' ',      '9', ' ', ' '}
    };
char partieIntermediaire[9][9] = 
    {
        {' ', '3', ' ',     ' ', '7', ' ',      ' ', '6', ' '},
        {'1', ' ', ' ',     ' ', ' ', '2',      '4', '5', ' '},
        {' ', ' ', '8',     ' ', '6', '3',      ' ', ' ', ' '},

        {' ', ' ', ' ',     ' ', ' ', ' ',      '3', '9', ' '},
        {'5', ' ', ' ',     ' ', ' ', ' ',      ' ', ' ', '1'},
        {' ', '9', '4',     ' ', ' ', ' ',      ' ', ' ', ' '},
        
        {' ', ' ', ' ',     '8', '2', ' ',      '7', ' ', ' '},
        {' ', '4', '1',     '7', ' ', ' ',      ' ', ' ', '2'},
        {' ', '7', ' ',     ' ', '4', ' ',      ' ', '8', ' '}
    };
char partieExpert[9][9] = 
    {
        {'7', '5', ' ',     ' ', '9', ' ',      ' ', ' ', '2'},
        {' ', ' ', ' ',     '4', ' ', '7',      ' ', ' ', ' '},
        {' ', ' ', '3',     ' ', '2', ' ',      ' ', ' ', '6'},

        {' ', '3', ' ',     ' ', ' ', ' ',      '9', ' ', ' '},
        {' ', ' ', ' ',     '6', ' ', '1',      ' ', ' ', ' '},
        {' ', ' ', '8',     ' ', ' ', ' ',      ' ', '7', ' '},
        
        {'5', ' ', ' ',     ' ', '6', ' ',      '1', ' ', ' '},
        {' ', ' ', ' ',     '9', ' ', '5',      ' ', ' ', ' '},
        {'1', ' ', ' ',     ' ', '8', ' ',      ' ', '2', '4'}
    };



// definition des fonctions

void sauvegarde(char grille[9][9]){
    char sauvegarde[30];
    FILE *fichier;
    printf("voulez vous sauvegarder votre partie (oui/non) ? ");
    scanf("%s", sauvegarde);
    if (sauvegarde[0] != 'o'){
        return;
    } else {
        printf("Nom du fichier de sauvegarde : ");
        scanf("%s",sauvegarde);
        fichier = fopen(sauvegarde, "w");
        for (int ligne = 0 ; ligne < 9 ; ligne ++){
            for (int colonne = 0 ; colonne < 9 ; colonne ++){
                fputc(grille[ligne][colonne], fichier);
            }
        }
        fclose(fichier);
    }
}

int chargePartie(char grille[9][9]){
    char nomFichier[30];
    FILE *fichier;
    printf("Nom du fichier à lire : ");
    scanf("%s",nomFichier);
    fichier = fopen(nomFichier,"r");
    if (fichier != NULL){
        printf("Chargement du fichier %s \n",nomFichier);
        for (int ligne = 0 ; ligne < 9 ; ligne ++){
            for (int colonne = 0 ; colonne < 9 ; colonne ++){
                grille[ligne][colonne] = fgetc(fichier);
            }
        }
        fclose(fichier);
        return 1;
    }else {
        printf("fichier %s inconnu\n", nomFichier);
        return 0;
    }
}

int testJeu(int ligne, int colonne, char valeur){
    if (ligne < 0) return 0;
    if (ligne > 9) return 0;
    if (colonne < 0) return 0;
    if (colonne > 9) return 0;
    if (valeur < '0') return 0;
    if (valeur > '9') return 0;
    return 1;
}

void afficheGrille(char grille[9][9]){
    printf("    1   2   3   4   5   6   7   8   9\n");
    printf("  +---+---+---+---+---+---+---+---+---+\n");
    for (int ligne = 0 ; ligne < 9 ; ligne++){
        printf("%d |", ligne + 1);
        for (int colonne = 0 ; colonne < 9 ; colonne++){
            printf(" %c |",grille[ligne][colonne]);
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+---+\n");
    }
}

void jouePartie(char grille[9][9]){
    int ligne, colonne;
    char valeur;
    int finJeu= 0;
    while (finJeu == 0){
        afficheGrille(grille);
        printf("0,0,0 => quitter\n");
        printf("Votre jeu (ligne, colonne, valeur) : ");
        scanf("%d, %d, %c", &ligne, &colonne, &valeur);
        //printf("ligne = %d, colonne = %d => valeur = %c\n", ligne, colonne, valeur);
        if (ligne == 0) {
            sauvegarde(grille);
            return;
        }
        if (testJeu(ligne, colonne, valeur) == 1){
            grille[ligne - 1][colonne - 1] = valeur;
        } else {
            printf("valeur Erronée : ligne, colonne, valeur\n");
            printf("mettre des virgules entre chaque valeur\n");
        }
    }
}

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

void aide(void){
    printf("afficher regles du jeu\n");
}

int main(void){

    // initialisation des variables
    char choixMenu = ' ';
    char tmpSaisie[5];

    // affichage du menu de choix
    while (choixMenu != '4'){
        printf("Jeu de sudoku\n");
        printf("Auteur : Simon Froger\n\n");
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