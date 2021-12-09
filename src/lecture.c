
/*
Inclusion du header associe.
*/
#include "lecture.h"

/*
Cette fonction donne un entier en sortie : 1 si le fichier existe ; 0 si le fichier n'existe pas.

Elle prend en parametre le chemin du fichier.
*/
int existeFichier(char* nomFichier){
	FILE* file = fopen(nomFichier,"r");
	
	if(file == NULL){
		return 0;
	}else{
		fclose(file);
		return 1;
	}
}

/*
Cette fonction calcule la frequence d'apparition d'un caractere dans un texte donne. 

Elle prend en parametre le caractere que l'on veut et le chemin du fichier.

Elle retourne un entier qui est la frequence du caractere.
*/
int freqChar(char carac, char* nomFichier){
	
	FILE* file;
	
	int compteur = 0;
	char val;
	
	if(!existeFichier(nomFichier)){
		printf("\nLe fichier %s n'existe pas.\n", nomFichier);
		exit(-1);
	}else{
		if((file=fopen(nomFichier, "r"))==NULL){
			printf("Erreur lors de l'ouverture du fichier %s.",nomFichier);
			exit(-1);
		}else{
			rewind(file);
			while((val = fgetc(file))!=EOF){
				if(val == carac){
					compteur++;
				}
			}
			fclose(file);
			return compteur;
		}
	}
}

/*
Cette fonction initialise la liste chainee pour y ranger les caracteres.

Elle prend en parametre la liste de caractere.

Elle retourne cette même liste.
*/
listeChar* initialisationListeChar(listeChar* liste){

    if((liste = (listeChar*) malloc(sizeof(listeChar)))==NULL){
		printf("\nErreur d'allocation memoire pour la liste de caractere.\n");
        exit(-1);
    }else{
    	return liste;
	}
}

/*
Cette procedure ajoute dans une liste chainee un element de type 'Caractere' (cf. 'lecture.h') de facon
a ce que l'element soit ajoute a la fon .

Elle prend en parametre un caractere, une frequence, un nouveau codage binaire, le nombre de bit
et la liste de caractere.

Cette procedure est utile durant la re creation de la liste de caractere apres une compression.
*/
void ajoutTabFin(char car, int frequence, char* bits, int nbrBits, listeChar* liste){
	Caractere* nCarac;
	
	if((nCarac = (Caractere*) malloc(sizeof(Caractere))) == NULL){
        exit(-1);
    }
	if((nCarac->newBits = (char*) malloc(nbrBits*sizeof(char))) == NULL){
        exit(-1);
    }   
	Caractere* current = liste->premier;

    if(current == NULL){
        nCarac->suivant = NULL;
        nCarac->carac = car;
		nCarac->frequence = frequence;
		nCarac->nbrBits = nbrBits;
		nCarac->newBits = bits;
        liste->premier = nCarac;
    }else{
        while (current->suivant != NULL)
        {
            current = current->suivant;
        }
        nCarac->carac = car;
		nCarac->frequence = frequence;
		nCarac->nbrBits = nbrBits;
		nCarac->newBits = bits;
        current->suivant = nCarac;
    }

}

/*
Cette procedure ajoute dans une liste chainee un element de type 'Caractere' (cf. 'lecture.h') de facon
a ce que la liste soit triee par ordre croissant selon les frequences de chaque caractere.

Elle prend en parametre la liste de caractere, un caractere et une frequence.

Cette procedure est utile pour la premiere creation de la liste de caractere.
*/
void ajoutListeChar(listeChar* liste, char carac, int freq){
	Caractere* nElement;
	
	if((nElement = (Caractere*) malloc(sizeof(Caractere))) == NULL){
		printf("Erreur malloc nElement char.");
		exit(-1);
	}

	//printf("\n-------Affiche Liste-----------\n");
	//afficherTabChar(liste);

	
	Caractere* previous = liste->premier;

	nElement->carac = carac;
	nElement->frequence = freq;
	nElement->nbrBits = 0;
	

	if(previous == NULL){
		liste->premier = nElement;
		nElement->suivant = NULL;
	}else{
		Caractere* current = liste->premier->suivant;

		if(nElement->frequence > previous->frequence){
			if(current == NULL){
				current = nElement;
				nElement->suivant = NULL;
			}else{
				while ((nElement->frequence > current->frequence) && (current->suivant != NULL))
				{
					previous = previous->suivant;
					current = current->suivant;
				}
				if(current->frequence <= nElement->frequence){
					nElement->suivant = current->suivant;
					current->suivant = nElement;
				}else{
					nElement->suivant = current;
					previous->suivant = nElement;
				}
			}
		}else{
			if(current == NULL){
				if(previous->carac != nElement->carac){
					nElement->suivant = liste->premier;
					liste->premier = nElement;
				}
			}else{
				while(current->suivant != NULL && current->frequence <= nElement->frequence){
					previous = previous->suivant;
					current = current->suivant;
				}
				nElement->suivant = current;
				previous->suivant = nElement;
			}
		}
	}
}

/*
Cette procedure parcours un fichier caractere par caractere.
Par la suite, ses cracteres sont ajoute a la liste chainee avec la procedure 'ajoutListeChar'.

Elle prend en parametre un chemin de fichier et la liste de caractere.

Elle est utile lors de la compression.
*/
void lectureTexte(char* nomFichier, listeChar* liste){

	FILE* file;
	char val;

	//Ce compteur permet de verifier si le caractere ('val') est deja present ou non dans la liste chainee.
	int compteur = 0;

	//Cette variable nous permet de naviguer dans la liste chaine.
	Caractere* position = liste->premier;

	if(!existeFichier(nomFichier)){
		printf("\n/Le fichier %s n existe pas./\n", nomFichier);
		exit(-1);
	}else{
		if((file=fopen(nomFichier, "r"))==NULL){
			printf("Erreur lors de l ouverture du fichier %s.",nomFichier);
			exit(-1);
		}else{
			rewind(file);
			while((val = fgetc(file))!=EOF){
				position = liste->premier;
				compteur = 0;
				if(position == NULL){
					ajoutListeChar(liste, val, freqChar(val,nomFichier));
				}else{
					while(position->suivant != NULL){
						position = position->suivant;
						if(position->carac == val){
							/*
							Si le caratere, stocke dans la variable 'var', existe deja dans la liste chaine,
							on incremente le compteur.
							*/
							compteur++;
						}
					}
					if (compteur == 0){
						ajoutListeChar(liste, val, freqChar(val, nomFichier));
					}
				}
			}
			fclose(file); 
		}
	}
}

/*
Cette procedure affiche le caractere et la frequence de la liste de caractere.

Elle prend en parametre la liste de caractere.
*/
void afficherTabChar(listeChar* liste){

	Caractere* current = liste->premier;

	while(current!= NULL){
		printf("\ncar=%c;freq=%d\n",current->carac, current->frequence);
		current = current->suivant;
	}
}

/*
Cette fonction traverse la liste chainee de caractere pour calculer le nombre d'element present.

Elle prend en parametre la liste de caractere.

Elle retourne un entier.
*/
int tailleListeChar(listeChar* liste){
	Caractere* current = liste->premier;

	int taille = 0;

	if(current == NULL){
		return -1;
	}else{
		while (current != NULL)
		{
			current = current->suivant;
			taille++;
		}
		return taille;
	}
}