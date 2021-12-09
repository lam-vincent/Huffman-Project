#ifndef LECTURE_H
#define LECTURE_H

/*  
    Le fichier header 'lecture.h' regroupe les structures et les fonctions pour le traitement des caracteres
	d'un fichier et de la liste de caracteres.
*/

/* Bibliothèques */

#include <stdio.h>
#include <stdlib.h>

/* Structures */

typedef struct Caractere {
	int frequence;
	char carac;
	int nbrBits;
	char* newBits;
	struct Caractere* suivant;
} Caractere;

typedef struct listeChar {
	Caractere *premier;
} listeChar;

/* Prototypes */

int existeFichier(char* nomFichier);
int freqChar(char carac, char* nomFichier);
void lectureTexte(char* nomFichier, listeChar* liste);
void ajoutTabFin(char car, int frequence, char* bits, int nbrBits, listeChar* liste);
void afficherTabChar(listeChar* liste);
listeChar* initialisationListeChar(listeChar* liste);
int tailleListeChar(listeChar* liste);
void ajoutListeChar(listeChar* liste, char carac, int freq);

#endif
