/*
Inclusion du header associe.
*/
#include "compression.h"

/*
Cette procedure execute toutes les fonctions necessaire pour la compression d'un fichier.
*/
void compression(listeChar* listeCarac, listeArbre* listTree, char* nomFichierEntre, char* nomFichierSortie) {
	printf("\nCompression\n");
	printf("\nFichier d'entree : %s\n", nomFichierEntre);
	lectureTexte(nomFichierEntre, listeCarac);
	creationListeArbre(listTree, listeCarac);
	creationArbre(listTree);

	//A ce stade nous pouvons afficher l'arbre situe en premiere position de la liste d'arbre.
	//print2D(listTree->premier->dataArbre);

	creationCodeBinaire(listTree, listeCarac);
	printf("\nFichier de sortie : %s\n", nomFichierSortie);
	ecritureFichier(nomFichierEntre, nomFichierSortie, listTree, listeCarac, listeCarac->premier->nbrBits);
}

/*
Cette fonction recupere la profondeur de l'arbre pour donner un nombre de bits maximal.

Elle prend en parametre un caractère, et un element de type 'Arbre' (cf. 'arbre_huff.h').

Elle retourne un entier.
*/
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

/*
Cette fonction retourne le plus grand entier entree deux entier donne.
*/
int max(int a, int b) {
	return (a < b ? b : a);
}

/*
Cette fonction retourne le plus petit entier entree deux entier donne.
*/
int min(int a, int b) {
	return (a < b ? a : b);
}

/*
Cette procedure permet de lancer la creation des nouveaux codes binaires.

Elle prend en parametre la liste d'arbre et la liste de caractere.
*/
void creationCodeBinaire(listeArbre* listTree, listeChar* listChar){

	// On se place au début de l'arbre, present dans la liste d'arbre, et debut liste de charactere.
	Arbre* arbreHuff= listTree->premier->dataArbre;
	Caractere* current = listChar->premier;

	char* newBits;

	// On calcule le nombre de bits pour chaque cractere.
	while (current != NULL)
	{
		current->nbrBits = calculNbrBits(current->carac, arbreHuff);

		current = current->suivant;
	}

	// On retourne au debut de la liste de caractere.
	current = listChar->premier;

	while (current != NULL)
	{
		// On ajoute plus de bits pour ne debirder dans la memoire.
		int nbrBits = current->nbrBits+3;

		if((newBits = (char*) malloc((nbrBits*sizeof(char)))) == NULL){
			printf("\nErreur allocation memoire pour newBits\n");
			exit(-1);
		}

		// On appelle cette procédure pour créer les nouveaux binaires.
		getNewBits(arbreHuff,newBits, nbrBits);

		current = current->suivant;
	}
}

/*
Cette procedure permet l'affichage du caractere et du nombre de bit associe.

Elle prend en parametre la liste de caractere.
*/
void afficherNbrBitsTabChar(listeChar* liste){

	Caractere* current = liste->premier;

	while(current!= NULL){
		printf("\ncar=%c;nbrBits=%d\n",current->carac, current->nbrBits);
		current = current->suivant;
	}
}

/*
Cette procedure permet l'affichage du caractere, le caractere en ASCII et les nouveaux bits associe.

Elle prend en parametre la liste de caractere.
*/
void afficherBitsTabChar(listeChar* liste){

	Caractere* current = liste->premier;

	while(current!= NULL){
		printf("\ncar=%c;car%d;bits=%s\n",current->carac, (int)current->carac,current->newBits);
		current = current->suivant;
	}
}

/*
Cette fonction donne un entier en sortie : 1 si l'arbre est une feuille ; 0 si l'arbre n'est pas une feuille.

Elle prend en parametre un element de type 'Arbre' (cf. 'arbre_huff.h').
*/
int estFeuille(Arbre* arbre){
	if((arbre->fd == NULL) && (arbre->fg == NULL)){
		return 1;
	}else{
		return 0;
	}
}
/*
Cette procedure parcours l'arbre et, pour chaques noeuds ou feuilles, elle va ajoute un 0 si il va a gauche
ou un 1 si il va droite à la chaine de caractere 'newBits' associe a la structure de 'Caractere' (cf. 'lecture.c').

En resume, chaques elements de l'arbre, que se soit une feuille ou un noeud, possedent un nouveau code binaire.
Mais la racine de l'arbre ne possede aucun nouveau code binaire.

Elle prend en parametre un arbre, une chaine de caractere et un entier (le nombre de bit).
*/
void getNewBits(Arbre* tree, char* newBits, int nbrBits){

	char un[2]="1";
	char zero[2]="0";

	if(tree!=NULL){
		// On verifie si l'arbre possede soit un fils gauche, soit un fils droit.
		if(tree->fg != NULL){

			if((tree->fg->dataChar->newBits = (char*) malloc((nbrBits*sizeof(char)))) == NULL){
				printf("\nErreur allocation memoire pour newBits\n");
				exit(-1);
			}
			// On fusionne la chaine de caractere passee en parametre avec la chaine nouvellement cree.
			strcat(tree->fg->dataChar->newBits, newBits);
			// On ajoute un 0 a la chaine de caractere puisque que nous allons vers le fils gauche.
			strcat(tree->fg->dataChar->newBits, zero);

			// On rappelle la procedure pour chaque noeud ou feuille de l'arbre.
			getNewBits(tree->fg, tree->fg->dataChar->newBits, nbrBits);
		}
		if(tree->fd != NULL){

			if((tree->fd->dataChar->newBits = (char*) malloc((nbrBits*sizeof(char)))) == NULL){
				printf("\nErreur allocation memoire pour newBits\n");
				exit(-1);
			}
			// On fusionne la chaine de caractere passee en parametre avec la chaine nouvellement cree.
			strcat(tree->fd->dataChar->newBits, newBits);
			// On ajoute un 1 a la chaine de caractere puisque que nous allons vers le fils droit.
			strcat(tree->fd->dataChar->newBits, un);

			// On rappelle la procedure pour chaque noeud ou feuille de l'arbre.
			getNewBits(tree->fd, tree->fd->dataChar->newBits, nbrBits);
		}
	}
}

/*
Cette procedure initilise le fichier de compression vierge.

Elle prend en parametre la destination du fichier.
*/
void initFichierSortieCompression(char* nomFichier){
    FILE* file = fopen(nomFichier, "a");

    if(file == NULL){
        printf("Fichier de sortie non creer.");
        exit(-1);
    }
    fclose(file);
}

/*
Cette procedure s'occupe de l'ecriture de facon compresser dans le fichier.

Elle prend en parametre le chemin du fichier d'entree, le chemin du fichier de sortie, la liste d'arbre,
la liste de cractere et le nombre de bits.
*/
void ecritureFichier(char* nomFichierEntre, char* nomFichierSortie, listeArbre* listTree, listeChar* listChar, int nbrBits){
    
	// On initialise le fichier de sortie.
    initFichierSortieCompression(nomFichierSortie);

	// On ouvre le fichier de sortie en mode ecriture seul.
    FILE* fileS = fopen(nomFichierSortie, "w");
    if(fileS == NULL){
        printf("Fichier de sortie non creer.");
        exit(-1);
    }

	// On ouvre le fichier de sortie en mode lecture seul.
    FILE* fileE = fopen(nomFichierEntre, "r");
    if(fileE == NULL){
        printf("Fichier d'entree non trouver.");
        exit(-1);
    }

    Caractere* current = listChar->premier;

	if(current == NULL){
		printf("\nListe de caractère vide.\n");
		exit(-1);
	}

    char val;

	// Cette variable est importante car c'est grace a elle que l'on peut coder de nouveau binaire.
    unsigned char bit = 0;

    int fill = 0;
    int taille = 0;
	int nbrCaractere = listTree->premier->dataArbre->dataChar->frequence;


    if(existeFichier(nomFichierSortie) && existeFichier(nomFichierEntre)){
		// On recopie dans le fichier la taille de la liste de caractere et le nombre de caractere present dans le fichier d'entree.
		fprintf(fileS, "%d;", tailleListeChar(listChar));
        fprintf(fileS, "%d;", nbrCaractere);
        while(current != NULL){
			/*
			On parcours la liste de caractere et on recopie la frequence, le cractere,
			la longueur de sa chaine binaire et son conde binaire.
			*/
            fprintf(fileS, "%d_%c_%lu_%s;", current->frequence, current->carac, strlen(current->newBits), current->newBits);
			current = current->suivant;
        }
		// On retourne au debut du fichier d'entree, celui que l'on veut compresser.
		rewind(fileE);

		// On retourne au debut de la liste de caractere
        current = listChar->premier;

		// On boucle tant que l'on peut lire des caracteres dans le fichier d'entree.
		while((fread(&val, sizeof(char), 1, fileE)>0)){

			while(current->carac != val){
				// On recherche le caractere dans la liste de caractere en fonction de celui lu dans le fichier.
				current = current->suivant;
			}
			// Une fois trouve, on recupere la taille de sa chaine de bit.
			taille = strlen(current->newBits);

			for(int i = 0; i<taille; i++) {
				// On avance de un bit pour mettre un 1 ou non.
				bit *=2;
				if(current->newBits[i] == '1') {
					bit += 1;
				}

				// On incremente un compteur pour savoir a quelle notre octet est rempli.
				fill++;

				//Lorsque l'on a constitue un octet entier, on l'ecrit dans le fichier de sortie et on remet a zero les variables.
				if(fill == 8) {
					fputc(bit, fileS);
					fill = 0;
					bit = 0;
				}
			}

			/*
			On revient au debut de la liste de caractere pour reiterer l'operation et on enleve un caractere
			de notrenombre de caractere.
			*/
			current = listChar->premier;
			nbrCaractere--;
		}
		/*
		Dans le cas ou l'on sort de la boucle, il faut verifier si on a pas oublie de donne.
		Si c'est le cas, on ecrit dans le fichier le reste de l'octet qu'il nous manque.
		*/
		if(fill != 0) {
			for(int i = 0; i<8-fill; i++){
				bit *= 2;
			}
			fputc(bit, fileS);
		}
		//printf("\nnbrCaractere=%d\n",nbrCaractere);
    }else{
        printf("\nLe fichier de sortie ou d'entrer n'existe pas\n");
		exit(-1);
    }

	// On ferme les deux fichiers.
	fclose(fileE);
    fclose(fileS);
}
