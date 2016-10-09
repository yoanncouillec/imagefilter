#include "pile.h"
#include <stdio.h>
#include <stdlib.h>

element *creer_element(image_t *img){
	element *elem;
	elem = malloc(sizeof(element));
	elem -> img = img;
	elem -> suivant = NULL;
	return elem;
}

element *ajouter_element(element *liste, element *elem){
	elem -> suivant = liste;
	return elem;
}

element *retirer_dernier(element *liste){
	element *l;
	if(liste != NULL){
		l = liste -> suivant;
		free(liste);
		return l;
	}
	else{
		return NULL;
	}
}
