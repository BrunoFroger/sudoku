#
#       makefile
#


CC=gcc
CFLAGS=-Wall -O -Werror
LDFLAGS=
EXEC=tests/tests sudoku 

SRCDIR = src
OBJDIR = obj
INCDIR = inc
EXEDST = exe

SRC= $(wildcard $(SRCDIR)/*.c)
OBJ= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(EXEC)
	tests/tests stopOnError

tests/tests.o : tests/test.c
	$(CC) -o $@ -c $^ $(CFLAGS)

tests/tests : tests/tests.o \
	obj/testJeu.o \
	obj/lireFichier.o \
	obj/afficheGrille.o \
	obj/grille.o \
	obj/solve.o
	$(CC) -o $@ $^ $(LDFLAGS)

sudoku: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

sudoku.o : nouvellePartie.h \
	jouePartie.h \
	regleDuJeu.h \
	chargePartie.h \
	lireFichier.h \
	generateur.h \
	afficheGrille.h \
	grille.h

chargePartie.o : lireFichier.h

efface.o : grille.h

generateur.o : solve.h \
	afficheGrille.h \
	testJeu.h \
	grille.h 

jouePartie.o : afficheGrille.h \
	sauvegarde.h \
	testJeu.h \
	aide.h \
	solve.h \
	grille.h

nouvellePartie.o : jouePartie.h \
	lireFichier.h \
	grille.h

solve.o : testJeu.h \
	afficheGrille.h \
	grille.h

testJeu.o : grille.h

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJDIR)/*.o core $(EXEC)
	rm tests/tests tests/tests.o
