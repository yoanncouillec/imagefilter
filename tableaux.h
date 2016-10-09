#ifndef TABLEAUX
#define TABLEAUX

typedef struct liste_img_{
	image_t *p_img;
	struct liste_img_ *suivant;
}liste_img;

void afficher_tab(unsigned char tab[], int taille);
void tri_bulle(unsigned char tab[], int taille);

#endif
