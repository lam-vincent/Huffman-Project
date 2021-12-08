#include "decompression.h"

void initFichierSortieDecompression(char* nomFichier){
    FILE* file = fopen(nomFichier, "a");

    if(file == NULL){
        printf("Fichier de sortie non creer.");
        exit(-1);
    }
    fclose(file);
}

void decompression(char* nomFichierEntre, char* nomFichierSortie, listeChar* listChar, listeArbre* listTree){

	initFichierSortieDecompression(nomFichierSortie);

    FILE* fileE = fopen(nomFichierEntre, "r");
    if(fileE == NULL){
        printf("Fichier d'entre non trouver.");
        exit(-1);
    }

    FILE* fileS = fopen(nomFichierSortie, "w");
    if(fileS == NULL){
        printf("Fichier d'entre non trouver.");
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

    if(existeFichier(nomFichierEntre)){
        //printf("\nExiste\n");
        fscanf(fileE, "%d;", &tailleListChar);
        fscanf(fileE, "%d;", &nbrCaractere);
		//printf("\ntaille=%d;nbrCarac=%d;\n", tailleListChar, nbrCaractere);
        while(tailleListChar != 0){
            fscanf(fileE, "%d_%c_%lu_", &frequence, &carac, &nbrBits);
            if(( tmpBits = (char*) malloc((nbrBits*sizeof(char)))) == NULL){
                printf("\nErreur allocation memoire pour newBits\n");
                exit(-1);
            }
            fscanf(fileE, "%[^;];", tmpBits);
            //printf("\nfreq=%d_char=%c_nbrBits=%lu_bin=%s;\n", frequence, carac, nbrBits,tmpBits);
            ajoutTabFin(carac, frequence, tmpBits, nbrBits, listChar);
            tailleListChar--;
        }

        //afficherTabChar(listChar);
        creationListeArbre(listTree, listChar);
	    creationArbre(listTree);

		Arbre* current = listTree->premier->dataArbre;
        rewind(fileS);
        //(val = fgetc(fileE))!=EOF
        while((fread(&val, sizeof(char), 1, fileE)>0)){
			//printf("\nval=%c\n", val);
            if(( bit = (char*) malloc((8*sizeof(char)))) == NULL){
                printf("\nErreur allocation memoire pour newBits\n");
                exit(-1);
			}
            
			for (int j = 7; j >= 0; j--){
				if(val & 1){
					bit[j] = '1';
				}else{
					bit[j] = '0';
				}
				val = val >> 1;
			}

			//printf("%s\n", bit);

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
			free(bit);
			//printf("\n");
		}

		//printf("\nnbrCaractere=%d\n",nbrCaractere);
    }else{
        printf("\nExiste pas\n");
    }

    fclose(fileS);
	fclose(fileE);
}


