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
	afficherNbrBitsTabChar(listeCarac);
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
		free(current->newBits);
		if((current->newBits = (char*) malloc(((current->nbrBits)+1)*sizeof(char))) == NULL){
			printf("\nErreur allocation memoire pour newBits\n");
			exit(-1);
		}
		getNewBits(arbreHuff, current->newBits);
		current = current->suivant;
	}
}

void afficherNbrBitsTabChar(listeChar* liste){

	Caractere* current = liste->premier;

	while(current!= NULL){
		printf("\ncar=%c;nbrBits=%d\n",current->carac, current->nbrBits);
		current = current->suivant;
	}
}

void afficherBitsTabChar(listeChar* liste){

	Caractere* current = liste->premier;

	while(current!= NULL){
		printf("\ncar=%c;bits=%s\n",current->carac, current->newBits);
		current = current->suivant;
	}
}

int estFeuille(Arbre* arbre){
	if((arbre->fd == NULL) && (arbre->fg == NULL)){
		return 1;
	}else{
		return 0;
	}
}

void getNewBits(Arbre* tree, char* newBits){
	
	char zero[2] = "0";
	char un[2] = "1";
	char end = '\0';
	
	if(estFeuille(tree)){
		strcat(newBits, &end);
		return;
	}
	getNewBits(tree->fg, strcat(newBits, zero));
	getNewBits(tree->fd, strcat(newBits, un));
}

