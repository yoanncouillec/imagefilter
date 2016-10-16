#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "pgm_image.h"
#include "trans_image.h"
#include "tableaux.h"

int main(int argc, char *argv[])
{
  char *source_name;
  char *destination_name;
  char *kernel_name;
  char *transformation;

  image_t *source;
  image_t *destination;
  noyau_t *kernel;
  int angle;
  int pourcent;
	
  int i = 1;
  while (i < argc) {
    if (strcmp (argv[i], "--input") == 0 || strcmp (argv[i], "-i") == 0) {
      source_name = argv[i+1];
      i++;
    }
    else if (strcmp (argv[i], "--output") == 0 || strcmp (argv[i], "-o") == 0) {
      destination_name = argv[i+1];
      i++;
    }
    else if (strcmp (argv[i], "--kernel") == 0 || strcmp (argv[i], "-k") == 0) {
      kernel_name = argv[i+1];
      i++;
    }
    else if (strcmp (argv[i], "--negative") == 0) {
      transformation = argv[i];
    }
    else if (strcmp (argv[i], "--rotate") == 0) {
      transformation = argv[i];
      angle = atoi(argv[i+1]);
      i++;
    }
    i++;
  }
  
  source = charger_image_pgm(source_name);
  //kernel = charger_noyau(kernel_name);

  if (strcmp (transformation, "--negative") == 0){
    destination = negatif(source);
  }
  else if (strcmp (transformation, "--rotate") == 0){
    destination = rotation_droite (source, angle);
  }
  sauver_image_pgm(destination_name, destination);
  return 0;
}

/*     case '2':{ //Rotation */
/*       printf("angle ? "); */
/*       scanf("%d",&angle); */
/*       dest = rotation_droite(src,angle); */
/*       if (dest != NULL){ */
/* 	//affiche_image(dest); */
/* 	elem = creer_element(dest); */
/* 	liste = ajouter_element(liste,elem); */
/*       } */
/*       break; */
/*     } */
/*     case '3':{ //Luminosite */
/*       printf("pourcent ? "); */
/*       scanf("%d",&pourcent); */
/*       dest = modifier_lumin(src,pourcent); */
/*       //affiche_image(dest); */
/*       elem = creer_element(dest); */
/*       liste = ajouter_element(liste,elem); */
/*       break; */
/*     } */
/*     case '4':{ //Convoluer */
/*       printf("nom ? "); */
/*       dest = convoluer(src, pn); */
/*       //affiche_image(dest);			 */
/*       elem = creer_element(dest); */
/*       liste = ajouter_element(liste,elem); */
/*       break; */
/*     } */
/*     case '5':{ //Bruiter */
/*       printf("pourcent ? "); */
/*       scanf("%d",&pourcent); */
/*       dest = bruiter_image(src,pourcent); */
/*       //affiche_image(dest);; */
/*       elem = creer_element(dest); */
/*       liste = ajouter_element(liste,elem); */
/*       break; */
/*     } */
/*     case '6':{ //Filtre Median */
/*       dest = filtrer_median(src); */
/*       //affiche_image(dest); */
/*       elem = creer_element(dest); */
/*       liste = ajouter_element(liste,elem); */
/*       break; */
/*     } */
/*     case 'S':{ //Sauver */
/*       printf("Sauvergarde de %s dans %s\n", argv[1], argv[2]); */
/*       break; */
/*     } */
/*     case 'U':{ //Undo */
/*       if (liste->suivant != NULL){ */
/* 	element *l = liste; */
/* 	detruire_image(liste -> img); */
/* 	liste = liste -> suivant; */
/* 	free(l); */
/* 	dest = liste -> img; */
/*       } */
/*       else{ */
/* 	printf("Fin des changements, c'est l'image originale !\n"); */
/*       } */
/*       //affiche_image(dest); */
/*       break; */
/*     } */
/*     case 'Q':{ //Exit */
/*       while (liste != NULL){ */
/* 	liste = retirer_dernier(liste); */
/*       } */
/*       printf("A bientot !\n"); */
/*       return 0; */
/*     } */
/*     default:{ */
/*       printf("Erreur de choix\n"); */
/*       break; */
/*     } */
/*     } */
/*     src = dest; */
/*   }	 */
/*   return 0; */
/* } */

/* char menu(){ // affiche un menu et verifie la saisie */
/*   char choix; */
/*   char chaine[50]; */
/*   do{ */
/*     printf("\n------------- Menu ------------\n"); */
/*     printf("Negatif (1)\n"); */
/*     printf("Rotation à droite (2)\n"); */
/*     printf("Modifier luminosité (3)\n"); */
/*     printf("Convoluer (4)\n"); */
/*     printf("Bruiter (5)\n"); */
/*     printf("Filtrer Median (6)\n"); */
/*     printf("Sauver (S)\n"); */
/*     printf("Undo (U)\n"); */
/*     printf("Quitter (Q)\n"); */
/*     //scanf("%c", &choix); */
/*     scanf("%s", chaine); */
/*     if (strlen(chaine) != 1){ */
/*       printf("Saisissez un seul caracatere !%d\n", (int) strlen(chaine)); */
/*       continue; */
/*     } */
/*     else{ */
/*       choix = chaine[0]; */
/*       printf("choix %c\n",choix); */
/*     } */
/*   }while((choix != '1') && (choix != '2') && (choix != '3') && (choix != '4') && (choix != '5') && (choix != '6') && (choix != 'S')&& (choix != 'Q') && (choix != 'U')); */
/*   return choix; */
/* } */
	
/* /\* void affiche_image(image_t * img) *\/ */
/* /\* 	{ *\/ */
/* /\* 	creer_fenetre(img->nx, img->ny, NULL, NULL);	 *\/ */
/* /\* 	afficher_img_ngris(img->buff,0,0,img->nx,img->ny); *\/ */
/* /\* 	attendre_fermeture_fenetre(); *\/ */
/* /\* 	} *\/ */
	
