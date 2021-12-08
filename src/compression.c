#include "compression.h"

void compression(listeChar* listeCarac, listeArbre* listTree, char* nomFichierEntre, char* nomFichierSortie) {
	printf("\nCompression\n");
	printf("\nFichier d'entre :%s\n", nomFichierEntre);
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
	printf("\nFichier de sortie :%s\n", nomFichierSortie);
	ecritureFichier(nomFichierEntre, nomFichierSortie, listTree, listeCarac, listeCarac->premier->nbrBits);
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
		printf("\ncar=%c;car%d;bits=%s\n",current->carac, (int)current->carac,current->newBits);
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

void initFichierSortieCompression(char* nomFichier){
    FILE* file = fopen(nomFichier, "a");

    if(file == NULL){
        printf("Fichier de sortie non creer.");
        exit(-1);
    }
    fclose(file);
}

void ecritureFichier(char* nomFichierEntre, char* nomFichierSortie, listeArbre* listTree, listeChar* listChar, int nbrBits){
    
    initFichierSortieCompression(nomFichierSortie);

    FILE* fileS = fopen(nomFichierSortie, "w");
    if(fileS == NULL){
        printf("Fichier de sortie non creer.");
        exit(-1);
    }

    FILE* fileE = fopen(nomFichierEntre, "r");
    if(fileE == NULL){
        printf("Fichier d'entre non trouver.");
        exit(-1);
    }

    Caractere* current = listChar->premier;

	if(current == NULL){
		printf("\nListe de caractère vide.\n");
		exit(-1);
	}

    char val;
    unsigned char bit = 0;
    int fill = 0;
    int taille = 0;
	int nbrCaractere = listTree->premier->dataArbre->dataChar->frequence;

    if(existeFichier(nomFichierSortie) && existeFichier(nomFichierEntre)){
        //printf("\nExiste\n");
		fprintf(fileS, "%d;", tailleListeChar(listChar));
        fprintf(fileS, "%d;", nbrCaractere);
        while(current != NULL){
			//printf("%d", current->frequence);
			//printf("%c_", current->carac);
			//printf("%lu_", strlen(current->newBits));
			//printf("%s;", current->newBits);
            fprintf(fileS, "%d_%c_%lu_%s;", current->frequence, current->carac, strlen(current->newBits), current->newBits);
			current = current->suivant;
        }
		rewind(fileE);
        current = listChar->premier;
		//(val = fgetc(fileE))!=EOF
		while((fread(&val, sizeof(char), 1, fileE)>0)){
            //printf("%c", val);
			while(current->carac != val){
                //printf("\ncurrent->carac=%c\n", current->carac);
				current = current->suivant;
			}
			//printf("\ntest1\n");
			//printf("current->caracSORTIE=%c\n", current->carac);
			taille = strlen(current->newBits);
			for(int i = 0; i<taille; i++) {
				bit *=2;
				if(current->newBits[i] == '1') {
					bit += 1;
				}
				fill++;
				if(fill == 8) {
					fputc(bit, fileS);
					//printf("-0x%02x\n", bit);
					//printf("%u\n", bit);
					fill = 0;
					bit = 0;
				}
			}
			current = listChar->premier;
			nbrCaractere--;
		}
		if(fill != 0) {
			for(int i = 0; i<8-fill; i++){
				bit *= 2;
			}
			fputc(bit, fileS);
		}
		//printf("\nnbrCaractere=%d\n",nbrCaractere);
    }else{
        printf("\nExiste pas\n");
    }

	fclose(fileE);
    fclose(fileS);
}
