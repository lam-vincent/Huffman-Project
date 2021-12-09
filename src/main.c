#include "header.h"

/*  
    Nous avons divise le plus possible le programme pour avoir deux fonctions principales qui la compression d'un cote et la decompression de l'autre.
    De ce fait, nous nous retrouvons avec une fonction main tres legere avec un fichier header.
*/

int main(int argc, char *argv[]) {

	//On initialise deux liste differentes pour stocker les caracteres d'un cote et les elements de l'arbre de l'autre.
	listeChar* tabChar=NULL;
	listeArbre* tabArbre=NULL;

	tabChar=initialisationListeChar(tabChar);
	tabArbre=initialisationListeArbre(tabArbre);

	/*
	On utilise un switch pour verifier rapidement des cas pre definis.
	Dans notre cas, on surveille si le second caractere du second parametre est soit un c, un d, ou h.
	Si ce n'est pas le cas ou si la chaine de caractere est trop longue, on affiche un message d'aide.
	*/

	int taille = strlen(argv[1]);

	if(taille == 2){
		switch(argv[1][1]) {
			case'c':
				compression(tabChar, tabArbre, argv[2], argv[3]);
			break;
			case'd':
				decompression(argv[2], argv[3], tabChar, tabArbre);
				//print2D(tabArbre->premier->dataArbre);
				printf("\nFichier d'entre :%s\n", argv[2]);
				printf("\nFichier de sortie :%s\n", argv[3]);
			break;
			case 'h':
				printf("\n./main/bin [-c | -d | -h] source_file target_file\n\n	-c	Compression du fichier source vers un nouveau fichier.\n	-d	Decompression d'un fichier deja compresse vers un nouveau fichier.\n	-h	Acceder l'aide de saisi.\n\n");
			break;
			default:
				printf("\nErreur de saisi. Entrer './bin/main -h' pour plus d'information.\n");
		}
	}else{
		printf("\nErreur de saisi. Entrer './bin/main -h' pour plus d'information.\n");
	}

	return 0;
}