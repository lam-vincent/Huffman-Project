#include "header.h"


int existeFichier(char* nomFichier){
	FILE* file = fopen(nomFichier,"r");
	
	if(file == NULL){
		printf("\n*Le fichier %s n existe pas.*\n", nomFichier);
		return 0;
	}else{
		fclose(file);
		printf("\n*Le fichier %s existe.*\n", nomFichier);
		return 1;
	}
}

int freqChar(char carac, char* nomFichier){
	
	FILE* file;
	
	int compteur = 0;
	char val;
	
	if(!existeFichier(nomFichier)){
		printf("\nLe fichier %s n existe pas.\n", nomFichier);
		exit(-1);
	}else{
		if((file=fopen(nomFichier, "r"))==NULL){
			printf("Erreur lors de l ouverture du fichier %s.",nomFichier);
			exit(-1);
		}else{
			while((val = fgetc(file))!=EOF){
				if(val == carac){
					compteur++;
				}
			}
			return compteur;
		}
	}
	
}

listeChar* initialisationListe(void){
    listeChar* tabCarac = (listeChar*) malloc(sizeof(listeChar*));

    if(tabCarac == NULL)
    {
        exit(-1);
    }

    return tabCarac;
}

void ajoutTab(char car, char* nomFichier, listeChar* liste){
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

void lectureTexte(char* nomFichier, listeChar* liste){
	FILE* file;
	char val;

	printf("\nsBin1\n");
	Caractere* position = liste->premier;
	printf("\nsBin2\n");

	if(!existeFichier(nomFichier)){
		printf("\nLe fichier %s n existe pas.\n", nomFichier);
		exit(-1);
	}else{
		if((file=fopen(nomFichier, "r"))==NULL){
			printf("Erreur lors de l ouverture du fichier %s.",nomFichier);
			exit(-1);
		}else{
			while((val = fgetc(file))!=EOF){
				if(position == NULL){
					ajoutTab(val,nomFichier, liste);
					position = liste->premier;
				}else{
					while(position->carac == val){
						position = position->suivant;
					}
					if(position->carac != val){
						ajoutTab(val, nomFichier, liste);
						position = tabCarac->premier;
					}
				}
				position = tabCarac->premier;
			}
			fclose(file); 
		}
	}
}

void afficherTab(listeChar* liste){

	Caractere* current = liste->premier;

	while(current!= NULL){
		printf("\ncar=%c;freq=%d",current->carac, current->frequence);
		current = current->suivant;
	}
}

int main(int argc, char *argv[]){

	tabCarac = initialisationListe();

	printf("\n%s\n", argv[1]);
	
	switch(argv[1][1]){
		case'c':
			printf("\nCompression\n");
			printf("\n%s\n",argv[2]);
			printf("\ntest1\n");
			lectureTexte(argv[2], tabCarac);
			printf("\ntest2\n");
			afficherTab(tabCarac);
			break;
		case'd':
			printf("\nDecomp resion\n");
			printf("\n%s\n",argv[2]);
			break;
		default:
			printf("\nErreur de saisi. Entrer en parametre c ou d.\n");
	}
	
	return 0;
}
