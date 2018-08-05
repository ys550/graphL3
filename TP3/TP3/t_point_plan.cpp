/*

Module : t_point_plan.c
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-22
*/

#include <stdlib.h>
#include <math.h>
#include "t_point_plan.h"


/********************************************************************/
/*				DECLARATIONS DE FONCTIONS PRIV�ES					*/
/********************************************************************/

/*
PRODUIT
Cod�e par  Youssef Soliman, Hugo Belin

Cette fonction calcul le produit des donn�es de deux tableaux
t_point_plan (multiplication des colonnes)

PARAM�TRES :
-tabA : premier tableau (type : t_point_plan *) 
-tabB : deuxieme tableau (type : t_point_plan *)
-taille :  la taille des deux tableaux (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: un tableau issu de la multiplication
des deux tableaux donn�s en param�tre ( pour les coordonn�es
en x et y) (type : t_point_plan *)
*/
static t_point_plan * produit(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
ECRAT_TYPE
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction calcul l'�cart type des donn�es du tableau
PARAM�TRES :
-tab : le tableau a d�terminer l'�cart type (type : t_point_plan *)
-taille : la taille du tableau (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: l'�cart type du tabeau (calcul� pour les
coordonn�es en x et en y) (type : t_point_plan)

*/
static t_point_plan ecart_type(t_point_plan * tab, int taille);

/*
ESPERANCE
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction calcul l'esp�rance (la moyenne) d'une matrice
t_point_plan (le fait pour les coordonn�es en x et y)

PARAM�TRES :
-tab : le tableau a moyenner (type : t_point_plan *)
-taille : la taille du tableau (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: l'esp�rance du tableau donn�
(pour les coordonn�es en x et y) (type : t_point_plan) 

*/
static t_point_plan esperance(t_point_plan * tab, int taille);



/*********************************************************/
/*          DEFINITIONS DES FONCTIONS PRIV�ES            */
/*********************************************************/

//-------------------------------------------------------------------

static t_point_plan * produit(t_point_plan * tabA, t_point_plan * tabB,
	int taille) {

	int i;
	t_point_plan * tab_produit;

	tab_produit = (t_point_plan *)malloc(taille * sizeof(t_point_plan));

	//si les deux tableau ne sont pas vide
	if (tabA != NULL && tabB != NULL && tab_produit != NULL) {
		//effectue le produit des valeurs x et y des deux tableau
		for (i = 0; i < taille; i++) {
			//place le produit dans le tableau retourne
			tab_produit[i].x = tabA[i].x * tabB[i].x;
			tab_produit[i].y = tabA[i].y * tabB[i].y;
		}
		return tab_produit;
	}
	else {
		return NULL;
	}

}

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

static t_point_plan esperance(t_point_plan * tab, int taille) {
	int i;
	t_point_plan somme;
	t_point_plan esperance;

	somme.x = 0;
	somme.y = 0;

	//Si le tablea n'est pas vide
	if (tab != NULL) {
		//effecture la somme
		for (i = 0; i < taille; i++) {
			somme.x += tab[i].x;
			somme.y += tab[i].y;
		}
		//effectue la moyenne
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

//-------------------------------------------------------------------

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

	//vide la tableau temporaire
	free(tab_produitAB);

	return correlation;
}

//-------------------------------------------------------------------

int trouver_col_min(t_point_plan ** mat_corr, int taille) {
	int i, j;
	int indice_col_min = 0;
	//la correlation totale d'une colone (valeur max d'une colone = taille * 2)
	double col_corr_tot = (double)(taille * 2);
	t_point_plan somme_col;

	for (i = 0; i < taille; i++) {

		somme_col.x = 0;
		somme_col.y = 0;

		//effectue la somme de chaque colone
		for (j = 0; j < taille; j++) {
			somme_col.x += mat_corr[j][i].x;
			somme_col.y += mat_corr[j][i].y;
		}

		//trouve la colone avec la plus petite somme
		if ((somme_col.x + somme_col.y) < col_corr_tot) {
			col_corr_tot = somme_col.x + somme_col.y;
			indice_col_min = i;
		}

	}

	return indice_col_min;
}

//-------------------------------------------------------------------

void detruire_matrice_pts(t_point_plan ** mat, int taille) {
	int i;
	t_point_plan * ptr_mat;

	/*detruit le contenue de la matrice 
	avant de detruire la matrice*/
	for (i = 0; i < taille; i++) {
		ptr_mat = mat[i];
		free(ptr_mat);
	}
		
	free(mat);
	mat = NULL;
}

//*****************************************************************************