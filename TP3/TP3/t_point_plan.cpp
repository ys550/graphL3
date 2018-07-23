#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "t_point_plan.h"


t_point_plan ** creer_matrice_pts(int taille) {
	int i;
	t_point_plan ** matrice_pts;

	matrice_pts = (t_point_plan **)malloc(taille * sizeof(t_point_plan *));

	for (i = 0; i < taille; i++)
		matrice_pts[i] = (t_point_plan *)malloc(taille * sizeof(t_point_plan));

	return matrice_pts;
}

t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille) {
	
	t_point_plan correlation;
	t_point_plan esperanceAB;
	t_point_plan esperanceA;
	t_point_plan esperanceB;
	t_point_plan ecartA;
	t_point_plan ecartB;
	t_point_plan * tab_produitAB;

	//A*B
	tab_produitAB = produit(tabA, tabB, taille);
	//E(AB)
	esperanceAB = esperance(tab_produitAB, taille);
	//E(A)
	esperanceA = esperance(tabA, taille);
	//E(B)
	esperanceB = esperance(tabB, taille);
	//o(A)
	ecartA = ecart_type(tabA, taille);
	//o(B)
	ecartB = ecart_type(tabB, taille);

	//valeur absolue de la correlation des x
	correlation.x = fabs(((esperanceAB.x - (esperanceA.x * esperanceB.x)) /
		(ecartA.x * ecartB.x)));

	//valeur absolue de la correlation des y
	correlation.y = fabs(((esperanceAB.y - (esperanceA.y * esperanceB.y)) /
		(ecartA.y * ecartB.y)));

	return correlation;
}

int trouver_col_min(t_point_plan ** mat_corr, int taille) {
	int i, j;
	int col_min = 0;
	double corr_tot = (double)(taille * 2);
	t_point_plan somme_col;

	for (i = 0; i < taille; i++) {
		for (j = 0; j < taille; j++) {
			somme_col.x += mat_corr[i][j].x;
			somme_col.y += mat_corr[i][j].y;
		}

		if ((somme_col.x + somme_col.y) < corr_tot) {
			corr_tot = somme_col.x + somme_col.y;
			col_min = i;
		}

		somme_col.x = 0;
		somme_col.y = 0;
	}

	return col_min;
}

void detruire_matrice_pts(t_point_plan ** mat, int taille) {
	int i;
	t_point_plan * ptr_mat;

	for (i = 0; i < taille; i++) {
		ptr_mat = mat[i];
		free(ptr_mat);
	}
		
	free(mat);
	mat = NULL;
}

static t_point_plan esperance(t_point_plan * tab, int taille) {
	int i;
	t_point_plan somme;
	t_point_plan esperance;

	somme.x = 0;
	somme.y = 0;

	if (tab != NULL) {
		for (i = 0; i < taille; i++) {
			somme.x += tab[i].x;
			somme.y += tab[i].y;
		}
		esperance.x = somme.x / taille;
		esperance.y = somme.y / taille;
	}

	return esperance;
}

static t_point_plan * produit(t_point_plan * tabA, t_point_plan * tabB,
	int taille) {

	int i;
	t_point_plan * tab_produit;

	tab_produit = (t_point_plan *)malloc(taille * sizeof(t_point_plan));

	if (tabA != NULL && tabB != NULL && tab_produit != NULL) {
		for (i = 0; i < taille; i++) {
			tab_produit[i].x = tabA[i].x * tabB[i].x;
			tab_produit[i].y = tabA[i].y * tabB[i].y;
		}
		return tab_produit;
	}
	else {
		return NULL;
	}

}

static t_point_plan ecart_type(t_point_plan * tab, int taille) {
	t_point_plan ecart_type;
	t_point_plan esperance_temp;

	//E(A^2) 
	t_point_plan * tab_valeurs_carre;
	//E(A)^2
	t_point_plan esperance_carre;

	//multipli le meme tableau par lui meme pour obtenir les valeurs au carre
	tab_valeurs_carre = produit(tab, tab, taille);

	//E(A)^2
	esperance_temp = esperance(tab, taille);
	esperance_carre.x = pow(esperance_temp.x, 2);
	esperance_carre.y = pow(esperance_temp.y, 2);

	//E(A^2) 
	esperance_temp = esperance(tab_valeurs_carre, taille);

	//l'ecart type est la racine carre de E(A^2) - E(A^2)
	ecart_type.x = sqrt((esperance_temp.x - esperance_carre.x));
	ecart_type.y = sqrt((esperance_temp.y - esperance_carre.y));

	return ecart_type;
}


