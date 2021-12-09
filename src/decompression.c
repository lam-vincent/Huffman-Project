/*
Inclusion du header associe.
*/
#include "decompression.h"

/*
Cette procedure initilise le fichier de decompression vierge.

Elle prend en parametre la destination du fichier.
*/
void initFichierSortieDecompression(char* nomFichier){
    FILE* file = fopen(nomFichier, "a");

    if(file == NULL){
        printf("Fichier de sortie non creer.");
        exit(-1);
    }
    fclose(file);
}

/*
Cette procedure execute toutes les fonctions necessaire pour la decompression d'un fichier.
Elle s'occupe de l'ecriture de facon decompresser dans le fichier.

Elle prend en parametre le chemin du fichier d'entree, le chemin du fichier de sortie, la liste de caractere et la liste d'arbre.
*/
void decompression(char* nomFichierEntre, char* nomFichierSortie, listeChar* listChar, listeArbre* listTree){

    printf("\nDecompression\n");

    // On initialise le fichier de sortie.
	initFichierSortieDecompression(nomFichierSortie);

    // On ouvre le fichier d'entree en mode lecture seul.
    FILE* fileE = fopen(nomFichierEntre, "r");
    if(fileE == NULL){
        printf("Fichier d'entree non trouver.");
        exit(-1);
    }
    
    // On ouvre le fichier de sortie en mode ecriture seul.
    FILE* fileS = fopen(nomFichierSortie, "w");
    if(fileS == NULL){
        printf("Fichier de sortie non trouver.");
        exit(-1);
    }
	

    int nbrCaractere;
    int tailleListChar;
    
    int frequence;
    char carac;
	unsigned long nbrBits;
	char* tmpBits;

    char val;
    char* bit;

    if(existeFichier(nomFichierSortie) && existeFichier(nomFichierEntre)){
		// On lit dans le fichier d'entree la taille de la liste de caractere et le nombre de caractere ecrit lors de la compression.
        fscanf(fileE, "%d;", &tailleListChar);
        fscanf(fileE, "%d;", &nbrCaractere);

		// On boucle selon la taille de la liste de caractere pour ne pas depasser sur le texte compresse.
        while(tailleListChar != 0){
			// On recupere la frequence, le caractere, le nombre de bit.
            fscanf(fileE, "%d_%c_%lu_", &frequence, &carac, &nbrBits);
            if(( tmpBits = (char*) malloc((nbrBits*sizeof(char)))) == NULL){
                printf("\nErreur allocation memoire pour newBits\n");
                exit(-1);
            }
			// On recupere  tous les elements jusqu'a un point virgule. Dans notre cas, on recupere le chaine de bits.
            fscanf(fileE, "%[^;];", tmpBits);

			// On l'ajoute ensuite a la liste de caractere.
            ajoutTabFin(carac, frequence, tmpBits, nbrBits, listChar);
            tailleListChar--;
        }

		// On cree la liste d'arbre et l'arbre a l'aide de la liste de caractere cree precedement.
        creationListeArbre(listTree, listChar);
	    creationArbre(listTree);

		// On se positionne sur la racine de l'arbre.
		Arbre* current = listTree->premier->dataArbre;

		// On se positionne au debut du fichier de sortie.
        rewind(fileS);

		// On boucle tant que l'on peut lire des caracteres dans le fichier d'entree.
        while((fread(&val, sizeof(char), 1, fileE)>0)){

			/*
			On alloue de la memoire a une variable de la taille d'un octet pour, que recuperer les bits ecris de facon
			compresser, soit accessible dans une chaine de caractere. 
			*/
            if(( bit = (char*) malloc((8*sizeof(char)))) == NULL){
                printf("\nErreur allocation memoire pour newBits\n");
                exit(-1);
			}

			/*
			On boucle de façon à ce que chaque bit, de la valeur recuperer dans le fichier, soit lu et
			ensuite ecrit dans la chaine de caratere nouvellement cree.
			*/
			for (int j = 7; j >= 0; j--){
				// Si on rencontre un bit valant 1, on met un '1' dans la chaine de caractere, sinon un '0'.
				if(val & 1){
					bit[j] = '1';
				}else{
					bit[j] = '0';
				}
				// On avance dans les bits.
				val = val >> 1;
			}

			/*
			On parcours ensuite selon l'octet recupere.
			On va dans le fils gauche si on recontre un 0,
			ou on va dans le fils droit si on rencontre un 1.
			Si on tombe sur une feuille, on ecris la valeur dans le fichier de sortie puis on remonte en haut de l'arbre.
			Enfin, on decremente le nombre de caractere lorsque l'on tombe sur feuille.
			*/
            for(int i = 0; i < 8 ; i++){
				//printf("%c_", bit[i]);

                if(bit[i] == '0'){
                    if(current->fg != NULL){
                        current = current->fg;
                    }else{
                        printf("\nErreur feuille atteinte\n");
                        exit(-1);
                    }
                }else if(bit[i] == '1'){
                    if(current->fd != NULL){
                        current = current->fd;
                    }else{
                        printf("\nErreur feuille atteinte\n");
                        exit(-1);
                    }
                }
                if(estFeuille(current)){
                    fprintf(fileS,"%c", current->dataChar->carac);
					//printf("%c", current->dataChar->carac);
                    current = listTree->premier->dataArbre;
					nbrCaractere--;
                }
            }
			// On libere l'espce de la chaine de caractere.
			free(bit);
			//printf("\n");
		}

		//printf("\nnbrCaractere=%d\n",nbrCaractere);
    }else{
        printf("\nLe fichier de sortie ou d'entrer n'existe pas\n");
		exit(-1);
    }

	// On ferme les deux fichiers.
    fclose(fileS);
	fclose(fileE);
}


