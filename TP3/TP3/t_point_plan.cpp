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
	return t_point_plan();
}

int trouver_col_min(t_point_plan ** mat_corr, int taille) {
	return 0;
}

void detruire_matrice_pts(t_point_plan ** mat, int taille) {

}

static t_point_plan calcul_esperance(t_point_plan * tab, int taille) {
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

static t_point_plan * calcul_ecart_type(t_point_plan * tab, int taille) {
	return nullptr;
}

static t_point_plan * calcul_produit(t_point_plan * tabA, t_point_plan * tabB,
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
