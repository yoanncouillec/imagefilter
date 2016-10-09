#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "noyau.h"

noyau_t *creer_noyau(unsigned int dim){
	noyau_t *noyau;
	
	noyau = malloc (sizeof(noyau_t));
	noyau->dim = dim;
	noyau->coeffs = malloc (dim * dim * sizeof(int));
	return noyau;
}

void detruire_noyau(noyau_t *pn){
	if (pn->coeffs != NULL){
		free (pn->coeffs);
	}
	free (pn);
}

noyau_t *charger_noyau(char *nom_fic){
	unsigned int dim;
	FILE *fichier;
	noyau_t *dest;
	int i,nb;
	
	if ( (fichier = fopen(nom_fic,"r")) == NULL){
		printf("Erreur d'ouverture de fichier\n");
		return NULL;
	}
	
	fscanf(fichier, "%ud", &dim);
	//printf("dim = %ud\n",dim);
	dest = creer_noyau(dim);
	for (i = 0; i < dim*dim; i++){
		fscanf(fichier,"%d",&nb);
		//printf("%d\n",nb);
		dest->coeffs[i] = nb;
	}
		
	return dest;
}
