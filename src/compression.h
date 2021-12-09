#ifndef COMPRESSION_H
#define COMPRESSION_H

/*
	Le fichier header 'compression.h' regroupe les fonctions necessaire pour la compression d'un fichier.
*/

/* Bibliothèques */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"
#include "arbre_huff.h"
#include "decompression.h"

/* Prototypes */

void compression(listeChar* listeCarac, listeArbre* listTree, char* nomFichierEntre, char* nomFichierSorti);
int calculNbrBits(char charRecherche, Arbre* tree);
int max(int a , int b);
int min(int a, int b);
void creationCodeBinaire(listeArbre* listTree, listeChar* listChar);
void afficherNbrBitsTabChar(listeChar* liste);
void afficherBitsTabChar(listeChar* liste);
int estFeuille(Arbre* arbre);
void getNewBits(Arbre* tree, char* newBits, int nbrBits);
void suppFeuilleGauche(Arbre* arbre);
void suppFeuilleDroite(Arbre* arbre);
void ecritureFichier(char* nomFichierEntre, char* nomFichierSortie, listeArbre* listTree, listeChar* listChar, int nbrBits);
void initFichierSortieCompression(char* nomFichier);

#endif