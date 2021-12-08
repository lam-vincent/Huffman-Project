#include "header.h"

int main(int argc, char *argv[]) {

	listeChar* tabChar=NULL;
	listeArbre* tabArbre=NULL;

	tabChar=initialisationListeChar(tabChar);
	tabArbre=initialisationListeArbre(tabArbre);

	//printf("\n%s\n", argv[1]);

	switch(argv[1][1]) {
		case'c':
			compression(tabChar, tabArbre, argv[2], argv[3]);
		break;
		case'd':
			printf("\nDecompression\n");
			decompression(argv[2], argv[3], tabChar, tabArbre);
			//print2D(tabArbre->premier->dataArbre);
			printf("\nFichier d'entre :%s\n", argv[2]);
			printf("\nFichier de sortie :%s\n", argv[3]);
		break;
		case 'h':
			printf("\n./main/bin [-c | -d | -h] source_file target_file\n\n	-c	Compression du fichier source vers un nouveau fichier.\n	-d	Decompression d'un fichier deja compresse vers un nouveau fichier.\n	-h	Acceder l'aide de saisi.\n\n");
		break;
		default:
			printf("\nErreur de saisi. Entrer l'argument -h pour plus d'information.\n");
	}

	return 0;
}