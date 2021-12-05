#include "compression.h"

void compression(listeChar* listeCarac, listeArbre* listTree, char* nomFichierEntre, char* nomFichierSorti) {
	printf("\nCompression\n");
	printf("\nentrer=%s\n", nomFichierEntre);
	lectureTexte(nomFichierEntre, listeCarac);
	//afficherTabChar(listeCarac);
	//printf("\ntest3_5\n");
	creationListeArbre(listTree, listeCarac);
	//printf("\ntest4\n");
	//afficherTabTree(listTree);
	creationArbre(listTree);
	//afficherTabTree(listTree);
	//printf("\ntailleTabChar=%i\n", tailleListeChar(listeCarac));
	//print2D(listTree->premier->dataArbre);
	//printf("\ntest5\n");
	creationCodeBinaire(listTree, listeCarac);
	//printf("\nnbrBits = %d\n", calculNbrBits('m', listTree->premier->dataArbre));
	//afficherNbrBitsTabChar(listeCarac);
	//afficherBitsTabChar(listeCarac);
	printf("\nsortie=%s\n", nomFichierSorti);
}

int calculNbrBits(char charRecherche, Arbre* tree) {

	if(tree != NULL) {

		if(tree->dataChar->carac==charRecherche) {
			return 0;
		} else {
			return 1 + max(calculNbrBits(charRecherche, tree->fg), calculNbrBits(charRecherche, tree->fd));
		}
	} else {
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

	char* newBits;


	while (current != NULL)
	{
		current->nbrBits = calculNbrBits(current->carac, arbreHuff);

		current = current->suivant;
	}

	current = listChar->premier;

	while (current != NULL)
	{
		int nbrBits = current->nbrBits+3;
		//print2D(listTree->premier->dataArbre);
		//printf("\ntest15\n");
		if((newBits = (char*) malloc((nbrBits*sizeof(char)))) == NULL){
			printf("\nErreur allocation memoire pour newBits\n");
			exit(-1);
		}
		//printf("\ntest16\n");
		getNewBits(arbreHuff,newBits, nbrBits);
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

void getNewBits(Arbre* tree, char* newBits, int nbrBits){

	char un[2]="1";
	char zero[2]="0";

	if(tree!=NULL){
		if(tree->fg != NULL){

			if((tree->fg->dataChar->newBits = (char*) malloc((nbrBits*sizeof(char)))) == NULL){
				printf("\nErreur allocation memoire pour newBits\n");
				exit(-1);
			}
			//printf("\nnewBitsG=%s\n", newBitsG);
			strcat(tree->fg->dataChar->newBits, newBits);
			strcat(tree->fg->dataChar->newBits, zero);
			//printf("\ntree->bg->fg->dataChar->newBits=%s\n",tree->bg->fg->dataChar->newBits);
			//printf("\nnewNodeBits=%s\n",newNodeBitsG);
			getNewBits(tree->fg, tree->fg->dataChar->newBits, nbrBits);
		}
		if(tree->fd != NULL){

			if((tree->fd->dataChar->newBits = (char*) malloc((nbrBits*sizeof(char)))) == NULL){
				printf("\nErreur allocation memoire pour newBits\n");
				exit(-1);
			}
			//printf("\nnewBitsD=%s\n", newBitsD);
			strcat(tree->fd->dataChar->newBits, newBits);

			strcat(tree->fd->dataChar->newBits, un);
			getNewBits(tree->fd, tree->fd->dataChar->newBits, nbrBits);
		}
	}
}
