#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"
#include "arbre_huff.h"
#include "compression.h"

void decompression(char* nomFichierEntre, char* nomFichierSortie, listeChar* listChar, listeArbre* listTree);
void initFichierSortieDecompression(char* nomFichier);

#endif