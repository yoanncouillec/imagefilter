#ifndef IMAGE_
#define IMAGE_

#define VAL(img,i,j) (img)->buff[(j)*(img)->nx+(i)]

typedef struct
	{
	unsigned long nx; //nombre de colonnes
	unsigned long ny; //nombre de lignes
	unsigned long nb_ng;
	unsigned char *buff;
	struct image_t *suivante;
	} image_t;

image_t *creer_image();

image_t *copier_image(image_t *src);

void detruire_image(image_t *p);
#endif
