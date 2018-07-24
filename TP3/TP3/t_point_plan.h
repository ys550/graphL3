/*

Module : t_point_plan.h
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-22
*/


/*
Le module t_point_plan contient des fonctions permettant de 
produire des calcules math�matiques avec des coordonn�es r�elles.

Dans ce module nous utilisons la structure t_point_plan qui contient
deux coordonn�es r�elle pour les coordonn�es en x et en y dans un 
plan math�matique.

Ce module contient les fonctions:

- t_point_plan ** creer_matrice_pts(int taille);
  (Cette fonction cr�e une matrice dynamique (tableau deux dimension de la 
taille souhait�)

- t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille);
  ( Cette fonction calucule la corr�lation lin�aire entre deux listes 
    de points-plan)

- int  trouver_col_min(t_point_plan ** mat_corr, int taille);
 ( Cette fonction re�ois une matrice de corr�lation et va trouver la plus
petite somme des colonnes de ce tableau.)

- void detruire_matrice_pts(t_point_plan ** mat, int taille);
  ( Cette fonction d�truit la m�moire allou�e � la matrice) 

Les autres fonction sont priv� a ce module (ce sont des fonctions math�matique
pour simplifier et ne pas r�p�ter le code).
Ce sont des fonctions pour caluler la moyenne, l'�cart type ou multiplier des tableau
t_point_plan.


*/



/*=========================================================*/
/*                       STRUCTURE                         */
/*=========================================================*/

typedef struct {
	// la position-pixel du point
	double x;   // coordonn�e horizontale
	double y;   // coordonn�e verticale
} t_point_plan;

/********************************************************************/
/*						DECLARATIONS DE FONCTIONS					*/
/********************************************************************/

/*
CREER_MATRICE_PTS
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction cr�e une matrice dynamique (tableau deux dimension de la 
taille souhait�)

PARAM�TRES :
-taille :  (type : int) taille de la matrice cr�e

HYPOTHESES: Aucune.

VALEUR DE RETOUR: l'adresse du tableau cr�� (type : t_point_plan **).

*/
t_point_plan ** creer_matrice_pts(int taille);

/*
CORRELATION_PTS
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction calucule la corr�lation lin�aire entre deux listes de points-plan 
(les deux listes doivent �tre de m�me taille)

PARAM�TRES :
-tabA : (type : t_point_plan *) premier tableau 
-tabB : (type : t_point_plan *) deuxieme tableau 
-taille : (type : int) la taille des deux tableaux 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan) la corr�lation lin�aire .

*/
t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
TROUVER_COL_MIN
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction re�ois une matrice de corr�lation et va trouver la plus
petite somme des colonnes de ce tableau.

PARAM�TRES :
-mat_corr : (type : t_point_plan **) la matrice ou nous cherchons 
			la colonne ou la somme est minimale.
-taille :  (type : int) la taille du tableau 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int).le num�ro de la colonne ou la somme des 
					donn�es est minimale.
*/
int  trouver_col_min(t_point_plan ** mat_corr, int taille);

/*
DETRUIRE_MATRICE_PTS
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction d�truit la m�moire allou�e � la matrice 
(d�truit les donn�es du tableau)

PARAM�TRES :
-mat : (type : t_point_plan **) matrice � d�truire
-taille :  (type : int) taille de la matrice 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  rien.
*/
void detruire_matrice_pts(t_point_plan ** mat, int taille);

/*
ESPERANCE
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction calcul l'esp�rance (la moyenne) d'une matrice 
t_point_plan (le fait pour les coordonn�es en x et y)

PARAM�TRES :
-tab : (type : t_point_plan *) le tableau a moyenner 
-taille :  (type : int) la taille du tableau 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan) l'esp�rance du tableau donn�
				   (pour les coordonn�es en x et y)

*/
static t_point_plan esperance(t_point_plan * tab, int taille);

/*
PRODUIT
Cod�e par  Youssef Soliman, Hugo Belin

Cette fonction calcul le produit des donn�es de deux tableaux 
t_point_plan (multiplication des colonnes) 

PARAM�TRES :
-tabA : (type : t_point_plan)  premier tableau 
-tabB : (type : t_point_plan *) deuxieme tableau 
-taille :  (type : int) la taille des deux tableaux 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan *) un tableau issu de la multiplication 
				   des deux tableaux donn�s en param�tre ( pour les coordonn�es
				   en x et y)
*/
static t_point_plan * produit(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
ECRAT_TYPE
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction calcul l'�cart type des donn�es du tableau 
PARAM�TRES :
-tab : (type : t_point_plan *) le tableau a d�terminer l'�cart type 
-taille :  (type : int) la taille du tableau 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan) l'�cart type du tabeau (calcul� pour les 
			        coordonn�es en x et en y) 

*/
static t_point_plan ecart_type(t_point_plan * tab, int taille);
