#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "pgm_image.h"
#include "trans_image.h"
#include "tableaux.h"
#include "pile.h"

char menu();
//void affiche_image(image_t * img);	

int main(int argc, char *argv[])
{
	if (argc < 3){
		fprintf(stderr, "usage : test_parser ficher_source fichier_dest [noyau]\n");
		exit(1);
	}
	
	image_t *src;
	image_t *dest;
	noyau_t *pn;
	element *liste = NULL;
	char choix = 0;
	int angle;
	int pourcent;
	int pos = 0;
	
	src=charger_image_pgm(argv[1]);
	//affiche_image(src);	
	pn = charger_noyau(argv[3]);
	element *elem = creer_element(src);
	liste = ajouter_element(liste,elem);
	dest = src;
	
	
	while (choix != 'Q'){
		choix = menu(pos);
		switch (choix){
			case '1':{ //Negatif
				dest = negatif(src);
				//affiche_image(dest);
				elem = creer_element(dest);
				liste = ajouter_element(liste,elem);
				break;
			}
			case '2':{ //Rotation
				printf("angle ? ");
				scanf("%d",&angle);
				dest = rotation_droite(src,angle);
				if (dest != NULL){
				  //affiche_image(dest);
					elem = creer_element(dest);
					liste = ajouter_element(liste,elem);
				}
				break;
			}
			case '3':{ //Luminosite
				printf("pourcent ? ");
				scanf("%d",&pourcent);
				dest = modifier_lumin(src,pourcent);
				//affiche_image(dest);
				elem = creer_element(dest);
				liste = ajouter_element(liste,elem);
				break;
			}
			case '4':{ //Convoluer
				printf("nom ? ");
				dest = convoluer(src, pn);
				//affiche_image(dest);			
				elem = creer_element(dest);
				liste = ajouter_element(liste,elem);
				break;
			}
			case '5':{ //Bruiter
				printf("pourcent ? ");
				scanf("%d",&pourcent);
				dest = bruiter_image(src,pourcent);
				//affiche_image(dest);;
				elem = creer_element(dest);
				liste = ajouter_element(liste,elem);
				break;
			}
			case '6':{ //Filtre Median
				dest = filtrer_median(src);
				//affiche_image(dest);
				elem = creer_element(dest);
				liste = ajouter_element(liste,elem);
				break;
			}
			case 'S':{ //Sauver
				sauver_image_pgm(argv[2], dest);
				printf("Sauvergarde de %s dans %s\n", argv[1], argv[2]);
				break;
			}
			case 'U':{ //Undo
				if (liste->suivant != NULL){
					element *l = liste;
					detruire_image(liste -> img);
					liste = liste -> suivant;
					free(l);
					dest = liste -> img;
				}
				else{
					printf("Fin des changements, c'est l'image originale !\n");
				}
				//affiche_image(dest);
				break;
			}
			case 'Q':{ //Exit
				while (liste != NULL){
					liste = retirer_dernier(liste);
				}
				printf("A bientot !\n");
				return 0;
			}
			default:{
				printf("Erreur de choix\n");
				break;
			}
		}
		src = dest;
	}	
	return 0;
}

char menu(){ // affiche un menu et verifie la saisie
	char choix;
	char chaine[50];
	do{
		printf("\n------------- Menu ------------\n");
		printf("Negatif (1)\n");
		printf("Rotation à droite (2)\n");
		printf("Modifier luminosité (3)\n");
		printf("Convoluer (4)\n");
		printf("Bruiter (5)\n");
		printf("Filtrer Median (6)\n");
		printf("Sauver (S)\n");
		printf("Undo (U)\n");
		printf("Quitter (Q)\n");
		//scanf("%c", &choix);
		scanf("%s", chaine);
		if (strlen(chaine) != 1){
		  printf("Saisissez un seul caracatere !%d\n", (int) strlen(chaine));
			continue;
		}
		else{
			choix = chaine[0];
			printf("choix %c\n",choix);
		}
	}while((choix != '1') && (choix != '2') && (choix != '3') && (choix != '4') && (choix != '5') && (choix != '6') && (choix != 'S')&& (choix != 'Q') && (choix != 'U'));
	return choix;
}
	
/* void affiche_image(image_t * img) */
/* 	{ */
/* 	creer_fenetre(img->nx, img->ny, NULL, NULL);	 */
/* 	afficher_img_ngris(img->buff,0,0,img->nx,img->ny); */
/* 	attendre_fermeture_fenetre(); */
/* 	} */
	
