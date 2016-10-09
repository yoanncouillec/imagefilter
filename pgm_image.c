#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm_image.h"

#define TAILLE_MAX 1024

image_t *charger_image_pgm(char *nom_fichier)
{
	FILE *fic;
	image_t *img = creer_image();
	unsigned long nx,ny, nbg;
	char *chaine = malloc(5);
	
	//printf("ouverture du fichier en écriture\n");
	fic = fopen (nom_fichier, "r");
	if (fic == NULL)
	{
		printf ("Erreur : nom de fichier incorrect\n");
		return NULL;
	}
	
	fscanf(fic, "%s\n", chaine);
	fscanf(fic, "%lu\n", &nx);
	fscanf(fic, "%lu\n", &ny);
	fscanf(fic, "%lu\n", &nbg);
	
	img->nx = nx;
	img->ny = ny;
	img->nb_ng = nbg; 

	if (strcmp (chaine, "P5") != 0)
	{
		printf("Erreur : le fichier ne contient P5 en première ligne\n");
		return NULL;
	}

	img->buff = malloc( (img->nx) * (img->ny) * sizeof (unsigned char) );	
	
	if (fread(img->buff, sizeof(unsigned char),  img->nx * img->ny, fic) != (img->nx * img->ny))
	{
		printf("Erreur : nombre de pixels lus incorrect\n");
		return NULL;
	}
	//printf("fermeture du fichier\n");
	fclose(fic);
	return img;
}

int sauver_image_pgm(char *nom_fichier, image_t *img)
{
	FILE *fichier = fopen(nom_fichier, "w");
	if (fichier == NULL)
	{
		printf("Erreur : ne peut pas ouvrir le fichier en écriture\n");
		return 1;
	}
	
	fprintf(fichier,"P5\n");
	fprintf(fichier,"%lu %lu\n%lu\n", img->nx, img->ny, img->nb_ng);
	
	fwrite(img->buff, sizeof(unsigned char),  img->nx * img->ny, fichier);
	fclose(fichier);
	return 1;
}
	
