# commande pour compiler
CC=gcc
CP=cp
RM=rm -ir
CFLAGS=-Wall

#nom des dossiers
SRC=src
OBJ=obj
DATA=data
SAVE=save

#arguments pour trouver les éléments dans les dossiers
SRCS=$(wildcard $(SRC)\*.c)
HEADS=$(wildcard $(SRC)\*.h)
OBJS=$(patsubst $(SRC)\%.c, $(OBJ)\%.o, $(SRCS))

RESTORESRC=$(wildcard $(SAVE)\*.c)
RESTOREHEAD=$(wildcard $(SAVE)\*.h)

#dossier pour l'executable
BINDIR=bin
BIN=$(BINDIR)\main

#varilable pour l'archivage
nameArchive=barre_romain

#programme du make
all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)\%.o: $(SRC)\%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean save restore give

save:
	@$(CP) $(SRCS) $(HEADS) $(SAVE)
	@echo Fichiers sauvegarde.

restore:
	@$(CP) $(RESTORESRC) $(RESTOREHEAD) $(SRC)
	@echo Sauvegarde restaure.

give:
	@mkdir $(nameArchive) $(nameArchive)\$(SRC) $(nameArchive)\$(SAVE) $(nameArchive)\$(BINDIR) $(nameArchive)\$(OBJ) $(nameArchive)\$(DATA) || echo Fichier deja existant.
	@$(CP) $(RESTORESRC) $(RESTOREHEAD) $(nameArchive)\$(SRC) || echo Rien a copier.
	@$(CP) Makefile $(nameArchive)\

clean:
	$(RM) $(BINDIR)\* $(OBJ)\* || echo Rien a supprimer
	$(RM) $(nameArchive) || echo Rien a supprimer
