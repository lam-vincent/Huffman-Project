#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct caractere {
	int frequence;
	char carac;
	struct caractere* suivant;
	
} Caractere;

typedef struct listeChar {
	Caractere *premier;
	
} listeChar;

typedef struct arb{
	Caractere carac;
    struct arb* fg;
    struct arb* fd;
} Arbre;

Arbre* arbre_compre = NULL;

listeChar* tabCarac = NULL;

int existeFichier(char* nomFichier);
int freqChar(char carac, char* nomFichier);
void lectureTexte(char* nomFichier, listeChar* liste);
void ajoutTabFin(char car,char* nomFichier, listeChar* liste);
void afficherTab(listeChar* liste);
listeChar* initialisationListe(void);
Caractere* ajoutTab(char car, char* nomFichier, listeChar* liste);

#endif
