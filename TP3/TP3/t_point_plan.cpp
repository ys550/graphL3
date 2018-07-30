/*

Module : t_point_plan.c
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-22
*/

#include <stdlib.h>
#include <math.h>
#include "t_point_plan.h"


/********************************************************************/
/*				DECLARATIONS DE FONCTIONS PRIVÉES					*/
/********************************************************************/

/*
PRODUIT
Codée par  Youssef Soliman, Hugo Belin

Cette fonction calcul le produit des données de deux tableaux
t_point_plan (multiplication des colonnes)

PARAMÈTRES :
-tabA : (type : t_point_plan *)  premier tableau
-tabB : (type : t_point_plan *) deuxieme tableau
-taille :  (type : int) la taille des deux tableaux

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan *) un tableau issu de la multiplication
des deux tableaux donnés en paramètre ( pour les coordonnées
en x et y)
*/
static t_point_plan * produit(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
ECRAT_TYPE
Codée par Youssef Soliman, Hugo Belin

Cette fonction calcul l'écart type des données du tableau
PARAMÈTRES :
-tab : (type : t_point_plan *) le tableau a déterminer l'écart type
-taille :  (type : int) la taille du tableau

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan) l'écart type du tabeau (calculé pour les
coordonnées en x et en y)

*/
static t_point_plan ecart_type(t_point_plan * tab, int taille);

/*
ESPERANCE
Codée par Youssef Soliman, Hugo Belin

Cette fonction calcul l'espérance (la moyenne) d'une matrice
t_point_plan (le fait pour les coordonnées en x et y)

PARAMÈTRES :
-tab : (type : t_point_plan *) le tableau a moyenner
-taille :  (type : int) la taille du tableau

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan) l'espérance du tableau donné
(pour les coordonnées en x et y)

*/
static t_point_plan esperance(t_point_plan * tab, int taille);



/*********************************************************/
/*          DEFINITIONS DES FONCTIONS PRIVÉES            */
/*********************************************************/

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

	// A^2
	t_point_plan * tab_valeurs_carre;
	//E(A)^2
	t_point_plan esperance_carre;

	//multipli le meme tableau par lui meme pour obtenir les valeurs au carre(A^2)
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


/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

t_point_plan ** creer_matrice_pts(int taille) {
	int i;
	t_point_plan ** matrice_pts;

	matrice_pts = (t_point_plan **)malloc(taille * sizeof(t_point_plan *));

	//Verification allocation dynamique
	if (!(matrice_pts))
		return NULL;

	for (i = 0; i < taille; i++) {
		matrice_pts[i] = (t_point_plan *)malloc(taille * sizeof(t_point_plan));
		//Verification allocation dynamique
		if (!(matrice_pts[i]))
			return NULL;
	}

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
	int indice_col_min = 0;
	//la correlation totale d'une colone (valeur max d'une colone = taille * 2)
	double col_corr_tot = (double)(taille * 2);
	t_point_plan somme_col;

	for (i = 0; i < taille; i++) {

		somme_col.x = 0;
		somme_col.y = 0;

		for (j = 0; j < taille; j++) {
			somme_col.x += mat_corr[j][i].x;
			somme_col.y += mat_corr[j][i].y;
		}

		if ((somme_col.x + somme_col.y) < col_corr_tot) {
			col_corr_tot = somme_col.x + somme_col.y;
			indice_col_min = i;
		}

	}

	return indice_col_min;
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