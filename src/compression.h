#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"
#include "arbre_huff.h"

void compression(listeChar* listeCarac, listeArbre* listTree, char* nomFichierEntre, char* nomFichierSorti);
int calculNbrBits(char charRecherche, Arbre* tree);
int max(int a , int b);
int min(int a, int b);
void creationCodeBinaire(listeArbre* listTree, listeChar* listChar);
void afficherBitsTabChar(listeChar* liste);


#endif