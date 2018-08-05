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

PARAM�TRES :
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
-taille : taille de la matrice cr�e (type : int)

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
-tabA : premier tableau (type : t_point_plan *)
-tabB : deuxieme tableau (type : t_point_plan *)
-taille : la taille des deux tableaux (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: la corr�lation lin�aire (type : t_point_plan).

*/
t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
TROUVER_COL_MIN
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction re�ois une matrice de corr�lation et va trouver la plus
petite somme des colonnes de ce tableau.

PARAM�TRES :
-mat_corr : la matrice ou nous cherchons (type : t_point_plan **) 
			la colonne ou la somme est minimale.
-taille :  la taille du tableau (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: le num�ro de la colonne ou la somme des 
					donn�es est minimale (type : int).
*/
int  trouver_col_min(t_point_plan ** mat_corr, int taille);

/*
DETRUIRE_MATRICE_PTS
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction d�truit la m�moire allou�e � la matrice 
(d�truit les donn�es du tableau)

PARAM�TRES :
-mat : matrice � d�truire (type : t_point_plan **)
-taille : taille de la matrice (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  rien.
*/
void detruire_matrice_pts(t_point_plan ** mat, int taille);