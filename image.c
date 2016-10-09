#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

image_t *creer_image()
{
	image_t *img = malloc( sizeof(image_t) );
	img -> nx = 0;
	img -> ny = 0;
	img -> nb_ng = 0;
	img -> buff = NULL;
	return img;
}

void detruire_image(image_t *p)
{
	if ( (p -> buff) != NULL ){
		free (p -> buff);
	}
	free (p);
}

image_t *copier_image(image_t *src)
{
	image_t *copie = creer_image();
	copie -> nx = src -> nx;
	copie -> ny = src -> ny;
	copie -> nb_ng = src -> nb_ng;
	copie -> buff = malloc( (src->nx) * (src->ny) * sizeof (unsigned char) );
	memcpy( copie -> buff, src -> buff, (src->nx) * (src->ny) * sizeof (unsigned char) );
	return copie;
}
