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
	obj/fichiers.o \
	obj/grille.o
	$(CC) -o $@ $^ $(LDFLAGS)

sudoku: $(OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)

sudoku.o : \
	fichiers.h \
	grille.h
	
grille.o : \
	fichiers.h 

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJDIR)/*.o core $(EXEC)
	rm tests/tests tests/tests.o
