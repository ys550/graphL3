/*

Module : t_point_plan.h
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-22
*/


/*
Le module t_point_plan contient des fonctions permettant de 
produire des calcules mathématiques avec des coordonnées réelles.

Dans ce module nous utilisons la structure t_point_plan qui contient
deux coordonnées réelle pour les coordonnées en x et en y dans un 
plan mathématique.

Ce module contient les fonctions:

- t_point_plan ** creer_matrice_pts(int taille);
  (Cette fonction crée une matrice dynamique (tableau deux dimension de la 
taille souhaité)

- t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille);
  ( Cette fonction calucule la corrélation linéaire entre deux listes 
    de points-plan)

- int  trouver_col_min(t_point_plan ** mat_corr, int taille);
 ( Cette fonction reçois une matrice de corrélation et va trouver la plus
petite somme des colonnes de ce tableau.)

- void detruire_matrice_pts(t_point_plan ** mat, int taille);
  ( Cette fonction détruit la mémoire allouée à la matrice) 

Les autres fonction sont privé a ce module (ce sont des fonctions mathématique
pour simplifier et ne pas répéter le code).
Ce sont des fonctions pour caluler la moyenne, l'écart type ou multiplier des tableau
t_point_plan.


*/



/*=========================================================*/
/*                       STRUCTURE                         */
/*=========================================================*/

typedef struct {
	// la position-pixel du point
	double x;   // coordonnée horizontale
	double y;   // coordonnée verticale
} t_point_plan;

/********************************************************************/
/*						DECLARATIONS DE FONCTIONS					*/
/********************************************************************/

/*
CREER_MATRICE_PTS
Codée par Youssef Soliman, Hugo Belin

Cette fonction crée une matrice dynamique (tableau deux dimension de la 
taille souhaité)

PARAMÈTRES :
-taille :  (type : int) taille de la matrice crée

HYPOTHESES: Aucune.

VALEUR DE RETOUR: l'adresse du tableau créé (type : t_point_plan **).

*/
t_point_plan ** creer_matrice_pts(int taille);

/*
CORRELATION_PTS
Codée par Youssef Soliman, Hugo Belin

Cette fonction calucule la corrélation linéaire entre deux listes de points-plan 
(les deux listes doivent être de même taille)

PARAMÈTRES :
-tabA : (type : t_point_plan *) premier tableau 
-tabB : (type : t_point_plan *) deuxieme tableau 
-taille : (type : int) la taille des deux tableaux 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan) la corrélation linéaire .

*/
t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
TROUVER_COL_MIN
Codée par Youssef Soliman, Hugo Belin

Cette fonction reçois une matrice de corrélation et va trouver la plus
petite somme des colonnes de ce tableau.

PARAMÈTRES :
-mat_corr : (type : t_point_plan **) la matrice ou nous cherchons 
			la colonne ou la somme est minimale.
-taille :  (type : int) la taille du tableau 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int).le numéro de la colonne ou la somme des 
					données est minimale.
*/
int  trouver_col_min(t_point_plan ** mat_corr, int taille);

/*
DETRUIRE_MATRICE_PTS
Codée par Youssef Soliman, Hugo Belin

Cette fonction détruit la mémoire allouée à la matrice 
(détruit les données du tableau)

PARAMÈTRES :
-mat : (type : t_point_plan **) matrice à détruire
-taille :  (type : int) taille de la matrice 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  rien.
*/
void detruire_matrice_pts(t_point_plan ** mat, int taille);

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

/*
PRODUIT
Codée par  Youssef Soliman, Hugo Belin

Cette fonction calcul le produit des données de deux tableaux 
t_point_plan (multiplication des colonnes) 

PARAMÈTRES :
-tabA : (type : t_point_plan)  premier tableau 
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
