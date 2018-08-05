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

Module : t_point_plan.h
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-22
*/

/*=========================================================*/
/*                       MACRO	                           */
/*=========================================================*/
/*
ARRONDIR

Cette macro permet d'arrondir un reel

PARAMÈTRES :
-x :  le numbre reel a arrondir

HYPOTHESES: Aucune.

VALEUR DE RETOUR: le reel arrondi en entier (type : int).

*/
#define ARRONDIR(x) (((int)(x + 0.5)))

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
-taille : taille de la matrice crée (type : int)

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
-tabA : premier tableau (type : t_point_plan *)
-tabB : deuxieme tableau (type : t_point_plan *)
-taille : la taille des deux tableaux (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: la corrélation linéaire (type : t_point_plan).

*/
t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
TROUVER_COL_MIN
Codée par Youssef Soliman, Hugo Belin

Cette fonction reçois une matrice de corrélation et va trouver la plus
petite somme des colonnes de ce tableau.

PARAMÈTRES :
-mat_corr : la matrice ou nous cherchons (type : t_point_plan **) 
			la colonne ou la somme est minimale.
-taille :  la taille du tableau (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: le numéro de la colonne ou la somme des 
					données est minimale (type : int).
*/
int  trouver_col_min(t_point_plan ** mat_corr, int taille);

/*
DETRUIRE_MATRICE_PTS
Codée par Youssef Soliman, Hugo Belin

Cette fonction détruit la mémoire allouée à la matrice 
(détruit les données du tableau)

PARAMÈTRES :
-mat : matrice à détruire (type : t_point_plan **)
-taille : taille de la matrice (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  rien.
*/
void detruire_matrice_pts(t_point_plan ** mat, int taille);