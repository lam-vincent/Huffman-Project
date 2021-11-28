#ifndef ARBRE_HUFF_H
#define ARBRE_HUFF_H

#include <stdio.h>
#include <stdlib.h>
#include "lecture.h"


typedef struct Arbre{
    struct Arbre* fg;
    struct Arbre* fd;
    Caractere* dataChar;  
}Arbre;

typedef struct elmtLstArb{
    struct elmtLstArb* suivant;
    Arbre* dataArbre; 
}elmtLstArb;

typedef struct listeArbre {
	elmtLstArb *premier;
} listeArbre;

Arbre* creerFeuille(Caractere* carac);
listeArbre* initialisationListeArbre(listeArbre* liste);
void creationListeArbre(listeArbre* listeTree, listeChar* listeCarac);
void ajoutListeArbre(listeArbre* liste, Arbre* node);
void afficherTabTree(listeArbre* liste);
void creationArbre(listeArbre* listTree);
Arbre* creerNode(listeArbre* listTree);
void suppresionListeArbre(listeArbre* liste, Arbre* supp);

void print2DUtil(Arbre* arbre, int space);
void print2D(Arbre* arbre);

#endif
