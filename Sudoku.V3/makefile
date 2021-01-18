#
#       makefile
#


CC=gcc
CFLAGS=-Wall -O -Werror
LDFLAGS=
EXEC=sudoku
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

sudoku: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

sudoku.o: nouvellePartie.h \
	jouePartie.h \
	regleDuJeu.h \
	chargePartie.h \
	lireFichier.h \
	generateur.h \
	afficheGrille.h

chargePartie.o : lireFichier.h

efface.o : lireFichier.h

generateur.o : solve.h \
	afficheGrille.h \
	testJeu.h

jouePartie.o : afficheGrille.h \
	sauvegarde.h \
	testJeu.h \
	aide.h \
	solve.h \
	efface.h \
	resetGrille.h

nouvellePartie.o : jouePartie.h \
	lireFichier.h 

resetGrille.o : lireFichier.h

solve.o : testJeu.h \
	afficheGrille.h \
	lireFichier.h

testJeu.o : lireFichier.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
    
clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC
