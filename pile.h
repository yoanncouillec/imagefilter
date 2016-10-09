#ifndef PILE
#define PILE
#include "image.h"

typedef struct element_{
	image_t *img;
	struct element_ *suivant;
}element;

element *creer_element(image_t *img);

element *ajouter_element(element *liste, element *elem);

element *retirer_dernier(element *liste);

#endif
