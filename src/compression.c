#include "compression.h"

void compression(listeChar* listeCarac, listeArbre* listTree, char* nomFichierEntre, char* nomFichierSorti) {
	printf("\nCompression\n");
	printf("\nentrer=%s\n", nomFichierEntre);
	lectureTexte(nomFichierEntre, listeCarac);
	afficherTabChar(listeCarac);
	printf("\ntest3_5\n");
	creationListeArbre(listTree, listeCarac);
	//printf("\ntest4\n");
	//afficherTabTree(listTree);
	creationArbre(listTree);
	//afficherTabTree(listTree);
	printf("\ntailleTabChar=%i\n", tailleListeChar(listeCarac));
	print2D(listTree->premier->dataArbre);
	printf("\ntest5\n");
	//printf("\nnbrBits = %d\n", calculNbrBits('m', listTree->premier->dataArbre))
	creationCodeBinaire(listTree, listeCarac);
	afficherBitsTabChar(listeCarac);
	printf("\nsortie=%s\n", nomFichierSorti);
}

int calculNbrBits(char charRecherche, Arbre* tree) {

	if(tree !=NULL) {

		if(tree->dataChar->carac==charRecherche) {
			return 0;
		} else {
			return 1 + max(calculNbrBits(charRecherche, tree->fg), calculNbrBits(charRecherche, tree->fd));
		}
	}
	else {
		return -1;
	}
}

int max(int a, int b) {
	return (a < b ? b : a);
}

int min(int a, int b) {
	return (a < b ? a : b);
}

void creationCodeBinaire(listeArbre* listTree, listeChar* listChar){

	Arbre* arbreHuff= listTree->premier->dataArbre;
	Caractere* current = listChar->premier;

	while (current!=NULL)
	{
		current->nbrBits = calculNbrBits(current->carac, arbreHuff);
		current = current->suivant;
	}
}

void afficherBitsTabChar(listeChar* liste){

	Caractere* current = liste->premier;

	while(current!= NULL){
		printf("\ncar=%c;bits=%d\n",current->carac, current->nbrBits);
		current = current->suivant;
	}
}