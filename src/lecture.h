#ifndef LECTURE_H
#define LECTURE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Caractere {
	int frequence;
	char carac;
	int nbrBits;
	struct Caractere* suivant;
} Caractere;

typedef struct listeChar {
	Caractere *premier;
} listeChar;

int existeFichier(char* nomFichier);
int freqChar(char carac, char* nomFichier);
void lectureTexte(char* nomFichier, listeChar* liste);
void ajoutTabFin(char car,char* nomFichier, listeChar* liste);
void afficherTabChar(listeChar* liste);
listeChar* initialisationListeChar(listeChar* liste);
Caractere* ajoutTab(char car, char* nomFichier, listeChar* liste);
void suppresion(listeChar* liste, Caractere* supp);

int tailleListeChar(listeChar* liste);

void ajoutListeChar(listeChar* liste, char carac, int freq);

#endif
