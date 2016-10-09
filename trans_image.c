#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "image.h"
#include "trans_image.h"
#include "tableaux.h"

#define VAL(img,i,j) (img)->buff[(j)*(img)->nx+(i)]
#define NBPIXELS(img) ((img)->nx * (img)->ny * sizeof(unsigned char))

//rend le negatif de l'image
image_t *negatif(image_t *src)
{
	int i;
	image_t *img = creer_image();
	img->nx = src->nx;
	img->ny = src->ny;
	img->nb_ng = src->nb_ng;
	img->buff = malloc (NBPIXELS(src));
	for(i = 0; i<NBPIXELS(src); i++)
	{
		img->buff[i] = 255 - src->buff[i];
	}
	
	return img;
	
}
// tourne l'image de "angle" degré
image_t *rotation_droite(image_t *src, int angle)
{
	image_t *copie = creer_image();	
	
	if (angle == 90){
		copie = transpose(src);
		copie = symetrie_verticale(copie);
	}
	else if (angle == 180){
		copie = symetrie_horizontale(src);
		copie = symetrie_verticale(copie);
	}
	else if (angle == 270){
		copie = transpose(src);
		copie = symetrie_horizontale(copie);
	}
	else
	{
		printf("Erreur : %d est un angle invalide\n",angle);
		return NULL;
	}
	return copie;
}
// donne le symetrique horizontal de la matrice
image_t *symetrie_horizontale(image_t *src)
{
	int i,j;
	image_t *copie = creer_image();
	copie->nx = src->nx;
	copie->ny = src->ny;
	copie->nb_ng = src->nb_ng;
	copie->buff = malloc( NBPIXELS(src) );
	
	for (i = 0; i < copie->nx; i++) 
	{
		for (j = 0; j < copie->ny; j++)
		{
			VAL(copie,i,copie->ny-j) = VAL(src,i,j);
		}
	}
	return copie;
}

// donne le symetrique vertical de la matrice
image_t *symetrie_verticale(image_t *src)
{
	int i,j;
	image_t *copie = creer_image();
	copie->nx = src->nx;
	copie->ny = src->ny;
	copie->nb_ng = src->nb_ng;
	copie->buff = malloc( NBPIXELS(src) );
	
	for (i = 0; i < copie->nx; i++)
	{
		for (j = 0; j < copie->ny; j++)
		{
			VAL(copie,copie->nx-i,j) = VAL(src,i,j);
		}
	}
	return copie;
}
// donne la transpose de la matrice
image_t *transpose(image_t *src)
{
	int i,j;
	image_t *copie = creer_image();
	copie->nx = src->ny;
	copie->ny = src->nx;
	copie->nb_ng = src->nb_ng;
	copie->buff = malloc( NBPIXELS(src) );
	
	for (i = 0; i < copie->nx; i++)
	{
		for (j = 0; j < copie->ny; j++)
		{
			VAL(copie,i,j) = VAL(src,j,i);
		}
	}
	return copie;
}

//modifier la luminosité d'une image
image_t *modifier_lumin(image_t *src, int pourcent)
{
	int i,j;
	image_t *copie = creer_image();
	copie->nx = src->nx;
	copie->ny = src->ny;
	copie->nb_ng = src->nb_ng;
	copie->buff = malloc( NBPIXELS(src) );
	for (i = 0; i < copie->nx; i++)
	{
		for (j = 0; j < copie->ny; j++)
		{
			int tmp = VAL(src,i,j) + (VAL(src,i,j)*pourcent/100);
			//printf("VAL = %ul, tmp = %ul\n",VAL(src,i,j), tmp);
			if (tmp >= 255)
			{
				VAL(copie,i,j) = 255;
			}
			else if (tmp < 0)
			{
				VAL(copie,i,j) = 0;
			}
			else
			{
				VAL(copie,i,j) = tmp;
			}		
		}
	}
	return copie;
}

//convoluer l'image
image_t *convoluer(image_t *src, noyau_t *pn)
	{
	image_t *dest = copier_image(src);
	int somme = 0;
	long somme_crt = 0;
	int i,j,ii,jj;
	int dim = pn->dim;
	int nx = src->nx;
	int ny = src->ny;
	//printf("nx = %d, ny = %d\n", nx, ny);
	
	for (jj = 0; jj < dim; jj++){
		for (ii = 0; ii < dim; ii++){
			somme += pn->coeffs[ jj*dim + ii];
		}
	}
	if (somme == 0) somme = 4;
	//printf("somme matrice = %d\n",somme);
	
	for (j = 0; j < ny; j++){ // parcoure chaque pixel
		for (i = 0; i < nx; i++){
			for (jj = 0; jj < dim; jj++){ // parcoure le noyau
				for (ii = 0; ii < dim; ii++){
					
					int c = i - dim/2 + ii;
					int l = j - dim/2 + jj;
					if (l < 0) l = 0;
					if (l > ny) l = ny -1;
					if (c < 0) c = 0;
					if (c > nx) c = nx -1;
					//printf("i:%d j:%d ii:%d j:%d l:%d c:%d\n",i,j,ii,jj,l,c);
					somme_crt += (pn->coeffs[jj * dim +ii]) * VAL(src,c,l);
				}
			}
			//printf("somme_crt = %ld\n",somme_crt);
			somme_crt = somme_crt / somme;
			//if (somme_crt < 0) somme_crt = 0 - somme_crt;
			VAL(dest,i,j) = somme_crt;
			
			somme_crt = 0;
		}
	}
	return dest;
}
//bruite l'image
image_t *bruiter_image(image_t *src, int pourcent){
	image_t *dest = copier_image(src);
	int i, nb, val;
	int taille = src->ny * src->nx;
	srand(time(NULL));
	for(i = 0; i < taille; i++){
		nb = rand() % 100;
		if(nb < pourcent){
			val = rand() % 256;
			dest->buff[i] = val;
		}
		else{
			dest->buff[i] = src->buff[i];
		}
	}
	return dest;
}				

image_t *filtrer_median(image_t *src){
	int i,j,ii,jj,taille, pos = 0;
	int nx,ny;
	int dim = 5;
	unsigned char tab[dim*dim -4];
	image_t *dest = copier_image(src);
	
	nx = src->nx;
	ny = src->ny;
	taille = src->ny * src->nx;
	
	for (j = 0; j < ny; j++){ // parcoure les pixels
		for (i = 0; i < nx; i++){	
			for (jj = 0; jj < dim; jj++){
				for (ii = 0; ii < dim; ii++){
					
					int c = i - dim/2 + ii;
					int l = j - dim/2 + jj;
					if (l < 0) l = 0;
					if (l > ny) l = ny -1;
					if (c < 0) c = 0;
					if (c > nx) c = nx -1;
					
					tab[pos] = VAL(src,c,l);
					pos++;
					
					/*if ((ii == 0) && (jj == 0))continue;
					if ((ii == (dim-1)) && (jj == 0))continue;
					if ((ii == (dim-1)) && (jj == (dim-1)))continue;
					if ((ii == 0) && (jj == (dim-1)))continue;*/
				}
				/*if ((ii == 0) && (jj == 0))continue;
				if ((ii == (dim-1)) && (jj == 0))continue;
				if ((ii == (dim-1)) && (jj == (dim-1)))continue;
				if ((ii == 0) && (jj == (dim-1)))continue;*/
			}
			tri_bulle(tab,dim*dim);
			VAL(dest,i,j) = tab[dim*dim/2];
			pos = 0;
		}
	}
	return dest;
}
					
					
					
					
					
					
					
					
					
