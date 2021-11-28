#include "header.h"

int main(int argc, char *argv[]) {

	listeChar* tabChar=NULL;
	listeArbre* tabArbre=NULL;

	tabChar=initialisationListeChar(tabChar);
	tabArbre=initialisationListeArbre(tabArbre);

	printf("\n%s\n", argv[1]);

	switch(argv[1][1]) {
		case'c':
			compression(tabChar, tabArbre, argv[2], argv[3]);
		break;
		case'd':
			printf("\nDecompression\n");
			printf("\nentre=%s\n", argv[2]);
			printf("\nsorti=%s\n", argv[3]);
		break;
		default:
			printf("\nErreur de saisi. Entrer en parametre c ou d.\n");
	}

	return 0;
}