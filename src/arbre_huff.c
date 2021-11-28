#include "arbre_huff.h"

listeArbre *initialisationListeArbre(listeArbre *liste) {
	liste=(listeArbre *)malloc(sizeof(listeArbre));

	if (liste==NULL) {
		exit(-1);
	}

	return liste;
}

Arbre *creerFeuille(Caractere *caracCreation) {

	Arbre *nArbre=(Arbre *)malloc(sizeof(Arbre));
	nArbre->dataChar=(Caractere *)malloc(sizeof(Caractere));

	if (nArbre==NULL || nArbre->dataChar == NULL) {
		printf("Erreur allocation memoire de nArbre.");
		exit(-1);
	}

	//printf("\nsBin_1\n");

	nArbre->dataChar=caracCreation;
	nArbre->fg=NULL;
	nArbre->fd=NULL;

	return nArbre;
}

void ajoutListeArbre(listeArbre *liste, Arbre *node) {
	elmtLstArb *nElement;

	if ((nElement=(elmtLstArb *)malloc(sizeof(elmtLstArb)))==NULL) {
		printf("Erreur malloc element.");
		exit(-1);
	}

	elmtLstArb *current=liste->premier;

	nElement->dataArbre=node;

	//printf("\nsBin_2\n");

	if (current==NULL) {
		//printf("\nsBin_3\n");
		nElement->suivant=NULL;
		liste->premier=nElement;
	} else {
		//printf("\nsBin_10\n");

		//printf("\ncurrent->dataArbre->dataChar->frequence=%d\n",current->dataArbre->dataChar->frequence);
		//printf("\nnode->dataChar->frequence=%d\n",node->dataChar->frequence);
		

		//printf("\nsBin_11\n");

		if (node->dataChar->frequence > current->dataArbre->dataChar->frequence) {
			//printf("\nsBin_4\n");
			while ((node->dataChar->frequence > current->dataArbre->dataChar->frequence) && current->suivant !=NULL) {
				current=current->suivant;
			}

			if (current->suivant==NULL) {
				//printf("\nsBin_6\n");
				current->suivant=nElement;
				nElement->suivant=NULL;
			}

			else {
				//printf("\nsBin_7\n");
				nElement->suivant=current->suivant;
				current->suivant=nElement;
			}
		}

		else {
			//printf("\nsBin_5\n");
			nElement->suivant=current->suivant;
			current->suivant=nElement;
		}
	}
}

void creationListeArbre(listeArbre *listeTree, listeChar *listeCarac) {
	Caractere *currentChar=listeCarac->premier;
	//elmtLstArb* currentTree = listeTree->premier;

	while (currentChar !=NULL) {
		//printf("\nsBin_9\n");
		ajoutListeArbre(listeTree, creerFeuille(currentChar));
		//printf("\nsBin_12\n");
		currentChar=currentChar->suivant;
	}
}

void afficherTabTree(listeArbre *liste) {

	elmtLstArb *current=liste->premier;

	while (current !=NULL) {
		printf("\nArbreCar=%c;ArbreFreq=%d\n", current->dataArbre->dataChar->carac, current->dataArbre->dataChar->frequence);
		current=current->suivant;
	}
}

void suppresionListeArbre(listeArbre *liste, Arbre *supp) {

	if (liste->premier==NULL) {
		printf("\nLa liste d arbre est vide\n");
		exit(-1);
	}

	elmtLstArb *previous=liste->premier;
	elmtLstArb *current=previous->suivant;

	if (current==NULL && previous==NULL) {
		printf("Erreur.");
		exit(-1);
	}

	else if (previous->dataArbre==supp) {
		liste->premier=previous->suivant;
		free(previous);
	}

	else {
		while (current !=NULL) {
			if (current->dataArbre==supp) {
				previous->suivant=current->suivant;
				free(current);
				return;
			}

			previous=current;
			current=current->suivant;
		}
	}
}

Arbre *creerNode(listeArbre *listTree) {

	Arbre *nNode=(Arbre *)malloc(sizeof(Arbre));
	nNode->dataChar=(Caractere *)malloc(sizeof(Caractere));

	Arbre *fils1=listTree->premier->dataArbre;
	Arbre *fils2=listTree->premier->suivant->dataArbre;

	if (fils1==NULL || fils2==NULL) {
		printf("Erreur. Fils vide.");
		exit(-1);
	}

	if (nNode==NULL) {
		printf("Erreur. nNode vide.");
		exit(-1);
	}

	nNode->dataChar->frequence=fils1->dataChar->frequence+fils2->dataChar->frequence;
	nNode->dataChar->carac='#';

	if (fils1->dataChar->frequence > fils2->dataChar->frequence) {
		nNode->fg=fils2;
		nNode->fd=fils1;
	}

	else {
		nNode->fg=fils1;
		nNode->fd=fils2;
	}

	suppresionListeArbre(listTree, fils1);
	suppresionListeArbre(listTree, fils2);

	return nNode;
}

void creationArbre(listeArbre *listTree) {
	elmtLstArb *current=listTree->premier;

	//printf("\nsBin_7.5\n");

	while (current->suivant !=NULL) {
		//printf("\nsBin_8\n");
		ajoutListeArbre(listTree, creerNode(listTree));
		//printf("\nsBin_10\n");
		current=listTree->premier;
		//afficherTabTree(listTree);
		//printf("\nsBin_11\n");
	}
}

void print2DUtil(Arbre *arbre, int espace) {

	if (arbre==NULL) {
		return;
	}

	espace+=10;

	print2DUtil(arbre->fd, espace);

	printf("\n");

	for (int i=10; i < espace; i++) {
		printf(" ");
	}

	printf("%c_%d\n", arbre->dataChar->carac, arbre->dataChar->frequence);

	print2DUtil(arbre->fg, espace);
}

void print2D(Arbre *arbre) {

	print2DUtil(arbre, 0);
}
