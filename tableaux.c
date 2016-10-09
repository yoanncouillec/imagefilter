#include <stdio.h>
#include <stdlib.h>

void afficher_tab(unsigned char tab[], int taille){
	int i;
	
	for(i = 0; i<taille; i++){
		printf("%d\n", tab[i]);
	}
}

void tri_bulle(unsigned char tab[], int taille){
	int i,j,tmp;
	
	for(i = taille-1; i > 0; i--){
		for(j = 0; j < i; j++){
			if(tab[j] > tab[j+1]){
				tmp = tab[j];
				tab[j] = tab[j+1];
				tab[j+1] = tmp;
			}
		}
	}
}

