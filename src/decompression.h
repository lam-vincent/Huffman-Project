#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

/*
	Le fichier header 'decrompression.h' regroupe les fonctions necessaire pour la decompression d'un fichier compresse.
*/

/* Bibliothèques */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"
#include "arbre_huff.h"
#include "compression.h"

/* Prototypes */

void decompression(char* nomFichierEntre, char* nomFichierSortie, listeChar* listChar, listeArbre* listTree);
void initFichierSortieDecompression(char* nomFichier);

#endif