/*
Inclusion du header associe.
*/
#include "arbre_huff.h"

/*
Cette fonction initialise la liste chainee pour y ranger les elements constituant l'arbre.
Cette liste permet de reunir plus facilement les feuilles et les noeuds pour construire l'arbre Huffman.

Elle prend en parametre la liste de d'arbre.

Elle retourne cette même liste.
*/
listeArbre *initialisationListeArbre(listeArbre *liste) {

	if((liste=(listeArbre *)malloc(sizeof(listeArbre)))==NULL){
		printf("\nErreur d'allocation memoire pour la liste d'arbre.\n");
		exit(-1);
	}else{
		return liste;
	}
}

/*
Cette fonction cree une feuille (element d'un arbre) a partir d'un caractere donne.

Elle prend en parametre un element de type 'Caractere'.

Elle retourne un element de type 'Arbre' (cf. 'arbre_huff.h').
*/
Arbre *creerFeuille(Caractere *caracCreation) {

	Arbre *nArbre=(Arbre *)malloc(sizeof(Arbre));
	nArbre->dataChar=(Caractere *)malloc(sizeof(Caractere));

	if (nArbre==NULL || nArbre->dataChar == NULL) {
		printf("Erreur allocation memoire de nArbre.");
		exit(-1);
	}

	nArbre->dataChar=caracCreation;
	nArbre->fg=NULL;
	nArbre->fd=NULL;

	return nArbre;
}

/*
Cette procedure ajoute dans une liste chainee un element de type 'Arbre' (cf. 'arbre_huff.h') de facon
a ce que la liste soit triee par ordre croissant selon les frequences de chaque caractere contenue dans une feuille
ou dans un noeud.

Elle prend en parametre la liste d'arbre et un element de type 'Arbre' (cf. 'arbre_huff.h').

Cette procedure est utile pour l'ajout des feuilles et des noeuds de l'arbre.
*/
void ajoutListeArbre(listeArbre *liste, Arbre *node) {
	elmtLstArb *nElement;

	if ((nElement=(elmtLstArb *)malloc(sizeof(elmtLstArb)))==NULL) {
		printf("Erreur malloc element.");
		exit(-1);
	}

	// On se place a la tete de la liste chainee.
	elmtLstArb *current=liste->premier;

	// On associe le nouvel element de la liste a un arbre.
	nElement->dataArbre=node;

	if (current==NULL) {

		// Si la liste est vide, on met l'element en premiere position et son suivant pointe sur 'NULL'.
		nElement->suivant=NULL;
		liste->premier=nElement;

	} else {
		
		/*
		Dans le cas d'une liste non vide, on compare la frenquence du caractere dans la feuille
		ou le noeud que l'on veut ajoute et la frequence des elements deja present dans la liste.
		*/
		if (node->dataChar->frequence > current->dataArbre->dataChar->frequence) {

			while ((node->dataChar->frequence > current->dataArbre->dataChar->frequence) && current->suivant !=NULL) {
				current=current->suivant;
			}
			// Si on se trouve en bout de liste, on ajoute l'element a la fin.
			if (current->suivant==NULL) {
				current->suivant=nElement;
				nElement->suivant=NULL;
			} else {
				// Sinon, on l'ajoute entre deux elements.
				nElement->suivant=current->suivant;
				current->suivant=nElement;
			}

		} else {
			/*
			Dans le cas ou la frenquence du caractere dans la feuille ou le noeud que l'on veut ajoute
			est plus petit que l'element ou l'on se trouve avec la variable 'current', on ajoute le nouvel element avant.
			*/
			nElement->suivant=current->suivant;
			current->suivant=nElement;

		}
	}
}

/*
Cette procedure permet la creation de la liste arbre avec uniquement en elements les feuilles
de l'arbre. Chaque feuille contient un caractere (cf. 'arbre_huff.h').

Elle prend en parametre la liste d'arbre et la liste de caractere.

Cette procedure est utile pour la creation et l'ajout, dans la liste d'arbre, des feuilles selon un caractere donne.
*/
void creationListeArbre(listeArbre *listeTree, listeChar *listeCarac) {

	// On positionne sur le premier element dans la liste chainee de caractere.
	Caractere *currentChar=listeCarac->premier;

	// On parcours cette liste et pour chauqe caractere, on cree une feuille que l'on ajoute a la liste chainee d'arbre.
	while (currentChar !=NULL) {
		ajoutListeArbre(listeTree, creerFeuille(currentChar));
		currentChar=currentChar->suivant;
	}
}

/*
Cette procedure affiche le caractere et la frequence de chaque element de type 'Arbre' (cf. 'arbre_huff.h')
de la liste chainee d'arbre.

Elle prend en parametre la liste d'arbre.
*/
void afficherTabTree(listeArbre *liste) {

	elmtLstArb *current=liste->premier;

	while (current !=NULL) {
		printf("\nArbreCar=%c;ArbreFreq=%d\n", current->dataArbre->dataChar->carac, current->dataArbre->dataChar->frequence);
		current=current->suivant;
	}
}

/*
Cette procedure permet la suppression d'element de la liste arbre.

Elle prend en parametre la liste d'arbre et l'element de type 'Arbre' a supprimer.

*/
void suppresionListeArbre(listeArbre *liste, Arbre *supp) {

	// On verifie si la liste d'arbre est vide ou non.
	if (liste->premier==NULL) {
		printf("\nLa liste d arbre est vide\n");
		exit(-1);
	}

	// On initialise de marquage de position afin de pas perdre d'element de la liste.
	elmtLstArb *previous=liste->premier;
	elmtLstArb *current=previous->suivant;

	if (current==NULL && previous==NULL) {
		printf("Erreur.");
		exit(-1);

	} else if (previous->dataArbre==supp) {
		// Si l'element a supprimer se trouve a la premiere position de la liste.
		liste->premier=previous->suivant;
		free(previous);

	} else {
		// Si l'element se trouve plus loin dans la liste.
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

/*
Cette fonction cree une noeud (element d'un arbre) a partir des feuilles et des autres noeuds presents
dans la liste arbre.

Elle prend en parametre la liste d'arbre.

Elle retourne un element de type 'Arbre' (cf. 'arbre_huff.h').
*/
Arbre *creerNode(listeArbre *listTree) {

	Arbre *nNode=(Arbre *)malloc(sizeof(Arbre));
	nNode->dataChar=(Caractere *)malloc(sizeof(Caractere));

	// On recupere les deux premiers elements de la liste arbre.
	Arbre *fils1=listTree->premier->dataArbre;
	Arbre *fils2=listTree->premier->suivant->dataArbre;

	if (fils1==NULL || fils2==NULL) {
		printf("Erreur. Fils vide.");
		exit(-1);
	}

	if (nNode==NULL || nNode->dataChar == NULL) {
		printf("Erreur. nNode vide ou nNode->dataChar vide.");
		exit(-1);
	}

	// On initialise la frequence du noeuds avec la somme des frequences de ses deux fils.
	nNode->dataChar->frequence=fils1->dataChar->frequence+fils2->dataChar->frequence;
	// On ilitialise son caractere avec '#'.
	nNode->dataChar->carac='#';

	// On fait en sorte de la fils ait une frequence plus petite que le fils droit.
	if (fils1->dataChar->frequence > fils2->dataChar->frequence) {
		nNode->fg=fils2;
		nNode->fd=fils1;
	}

	else {
		nNode->fg=fils1;
		nNode->fd=fils2;
	}

	// On supprime les fils de la liste d'arbre pour eviter des doublures.
	suppresionListeArbre(listTree, fils1);
	suppresionListeArbre(listTree, fils2);

	return nNode;
}

/*
Cette procedure permet la creation de l'arbre avec uniquement les feuilles de l'arbre.
Chaque feuille est utilisee pour un noeud et le re inserer dans la liste d'arbre.

Elle prend en parametre la liste d'arbre.

Cette procedure est utile pour la creation de l'arbre Huffman.
*/
void creationArbre(listeArbre *listTree) {
	elmtLstArb *current=listTree->premier;

	while (current->suivant !=NULL) {
		ajoutListeArbre(listTree, creerNode(listTree));
		current=listTree->premier;
	}
}

/*
Les deux fonctions suivantes permettent d'afficher un arbre binaire horizontalement.
*/
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
