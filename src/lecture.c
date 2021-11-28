#include "lecture.h"

int existeFichier(char* nomFichier){
	FILE* file = fopen(nomFichier,"r");
	
	if(file == NULL){
		return 0;
	}else{
		fclose(file);
		return 1;
	}
}

int freqChar(char carac, char* nomFichier){
	
	FILE* file;
	
	int compteur = 0;
	char val;
	
	if(!existeFichier(nomFichier)){
		printf("\n*Le fichier %s n existe pas.*\n", nomFichier);
		exit(-1);
	}else{
		if((file=fopen(nomFichier, "r"))==NULL){
			printf("Erreur lors de l ouverture du fichier %s.",nomFichier);
			exit(-1);
		}else{
			rewind(file);
			while((val = fgetc(file))!=EOF){
				if(val == carac){
					compteur++;
					//printf("\nval=%c ; carac=%c ; compteur=%i",val, carac, compteur);
				}
			}
			//rewind(file);
			fclose(file);
			return compteur;
		}
	}
}

listeChar* initialisationListeChar(listeChar* liste){
    liste = (listeChar*) malloc(sizeof(listeChar));

    if(liste == NULL)
    {
        exit(-1);
    }

    return liste;
}

void ajoutTabFin(char car, char* nomFichier, listeChar* liste){
	Caractere* nCarac;
	
	if((nCarac = (Caractere*) malloc(sizeof(Caractere))) == NULL){
        exit(-1);
    }
    
	Caractere* current = liste->premier;
    if(current == NULL){
        nCarac->suivant = NULL;
        nCarac->carac = car;
		nCarac->frequence = freqChar(car, nomFichier);
        liste->premier = nCarac;
    }else{
        while (current->suivant != NULL)
        {
            current = current->suivant;
        }
        nCarac->suivant = NULL;
        nCarac->carac = car;
		nCarac->frequence = freqChar(car, nomFichier);
        current->suivant = nCarac;
    }

}

Caractere* ajoutTab(char car, char* nomFichier, listeChar* liste){
	Caractere* nCarac;
	
	if((nCarac = (Caractere*) malloc(sizeof(Caractere))) == NULL){
        exit(-1);
    }

    nCarac->suivant = NULL;
    nCarac->carac = car;
	nCarac->frequence = freqChar(car, nomFichier);

	return nCarac;

}

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
				nElement->suivant = liste->premier;
				liste->premier = nElement;
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


void lectureTexte(char* nomFichier, listeChar* liste){
	FILE* file;
	char val;
	int compteur = 0;


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
					//ajoutTabFin(val,nomFichier, liste);
				}else{
					//printf("\nval=%c\n",val);
					while(position->suivant != NULL){
						position = position->suivant;
						if(position->carac == val){
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

void afficherTabChar(listeChar* liste){

	Caractere* current = liste->premier;

	while(current!= NULL){
		printf("\ncar=%c;freq=%d\n",current->carac, current->frequence);
		current = current->suivant;
	}
}

void suppresion(listeChar* liste, Caractere* supp){

    if(liste->premier == NULL)
    {
        printf("\nliste vide\n");
        exit(-1);
    }

    Caractere* predecedent = liste->premier;
    Caractere* current = predecedent->suivant;

    if(current == NULL || predecedent == NULL){
        printf("erreur");
        exit(-1);
    }else if(predecedent == supp){
        liste->premier = predecedent->suivant;
        free(predecedent);
    }else{
        while(current != NULL){
            if(current == supp){
                predecedent->suivant = current->suivant;
                free(current);
                return;
            }
            predecedent = current;
            current = current->suivant;
        }
    }
}

int tailleListeChar(listeChar* liste){
	Caractere* current = liste->premier;

	int taille = 0;

	while (current != NULL)
	{
		current = current->suivant;
		taille++;
	}
	
	return taille;
}