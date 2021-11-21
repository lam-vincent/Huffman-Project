#include "header.h"

int existeFichier(char *nomFichier)
{
	FILE *file = fopen(nomFichier, "r");

	if (file == NULL)
	{
		return 0;
	}
	else
	{
		fclose(file);
		return 1;
	}
}

int freqChar(char carac, char *nomFichier)
{

	FILE *file;

	int compteur = 0;
	char val;

	if (!existeFichier(nomFichier))
	{
		printf("\n*Le fichier %s n existe pas.*\n", nomFichier);
		exit(-1);
	}
	else
	{
		if ((file = fopen(nomFichier, "r")) == NULL)
		{
			printf("Erreur lors de l ouverture du fichier %s.", nomFichier);
			exit(-1);
		}
		else
		{
			rewind(file);
			while ((val = fgetc(file)) != EOF)
			{
				if (val == carac)
				{
					compteur++;
				}
			}
			rewind(file);
			fclose(file);
			return compteur;
		}
	}
}

listeChar *initialisationListe(void)
{
	listeChar *tabCarac = (listeChar *)malloc(sizeof(listeChar *));

	if (tabCarac == NULL)
	{
		exit(-1);
	}

	return tabCarac;
}

void ajoutTabFin(char car, char *nomFichier, listeChar *liste)
{
	Caractere *nCarac;

	if ((nCarac = (Caractere *)malloc(sizeof(Caractere))) == NULL)
	{
		exit(-1);
	}

	Caractere *current = liste->premier;
	if (current == NULL)
	{
		nCarac->suivant = NULL;
		nCarac->carac = car;
		nCarac->frequence = freqChar(car, nomFichier);
		liste->premier = nCarac;
	}
	else
	{
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

Caractere *ajoutTab(char car, char *nomFichier, listeChar *liste)
{
	Caractere *nCarac;

	if ((nCarac = (Caractere *)malloc(sizeof(Caractere))) == NULL)
	{
		exit(-1);
	}

	nCarac->suivant = NULL;
	nCarac->carac = car;
	nCarac->frequence = freqChar(car, nomFichier);

	return nCarac;
}

void lectureTexte(char *nomFichier, listeChar *liste)
{
	FILE *file;
	char val;
	int compteur = 0;

	Caractere *position = liste->premier;

	if (!existeFichier(nomFichier))
	{
		printf("\n/Le fichier %s n existe pas./\n", nomFichier);
		exit(-1);
	}
	else
	{
		if ((file = fopen(nomFichier, "r")) == NULL)
		{
			printf("Erreur lors de l ouverture du fichier %s.", nomFichier);
			exit(-1);
		}
		else
		{
			rewind(file);
			while ((val = fgetc(file)) != EOF)
			{
				position = liste->premier;
				compteur = 0;
				if (position == NULL)
				{
					ajoutTabFin(val, nomFichier, liste);
				}
				else
				{
					// printf("\nval=%c\n",val);
					if (position->carac != val)
					{
						while (position->suivant != NULL)
						{
							position = position->suivant;
							if (position->carac == val)
							{
								compteur++;
							}
						}
						// printf("\ncompteur = %d\n", compteur);
						if (compteur == 0)
						{
							// printf("\nval=%c\n",val);
							position->suivant = ajoutTab(val, nomFichier, liste);
						}
					}
				}
			}
			fclose(file);
		}
	}
}

void afficherTab(listeChar *liste)
{

	Caractere *current = liste->premier;

	while (current != NULL)
	{
		printf("\ncar=%c;freq=%d\n", current->carac, current->frequence);
		current = current->suivant;
	}
}

void bubbleSort(struct Caractere *start)
{
	int swapped, i;
	Caractere *ptr1;
	Caractere *lptr = NULL;

	if (start == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->suivant != lptr)
		{
			if (ptr1->frequence > ptr1->suivant->frequence)
			{
				swap(ptr1, ptr1->suivant);
				swapped = 1;
			}
			ptr1 = ptr1->suivant;
		}
		lptr = ptr1;
	} while (swapped);
}

void swap(Caractere *a, Caractere *b)
{
	int temp = a->frequence;
	a->frequence = b->frequence;
	b->frequence = temp;
}

int main(int argc, char *argv[])
{

	tabCarac = initialisationListe();

	printf("\n%s\n", argv[1]);

	switch (argv[1][1])
	{
	case 'c':
		printf("\nCompression\n");
		printf("\n%s\n", argv[2]);
		lectureTexte(argv[2], tabCarac);
		// printf("\ntest2\n");
		// afficherTab(tabCarac);
		break;
	case 'd':
		printf("\nDecomp resion\n");
		printf("\n%s\n", argv[2]);
		break;
	default:
		printf("\nErreur de saisi. Entrer en parametre c ou d.\n");
	}

	return 0;
};
