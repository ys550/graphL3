/*

Ce module à pour but de dessiner dans le mode graphique les
obstacles ( forme géométrique ).

Les informations des formes géométriques sont contenues dans des
fichers textes qui seront lus et utilisées dans dans les fonctions
de ce module.

Les fonctions utilisées ( lectures des données, création du mode graphique,
création du parcours avec la création des formes géométrique) :

- int lire_obstacles(char *nom_fich, t_liste_obs *obstacles);
( Cette fonction reçoit le nom du fichier à lire et va récupérer
toutes les informations de l'obstacle )

- void dessiner_obstacles(const t_liste_obs * obstacles);
( Cette fonction reçois la liste d'obstacle et va dessiner chaque forme
géométrique de cette liste )

- void detruire_obstacles(t_liste_obs * obstacles);
( Cette fonction détruit la liste d'obstacle qui à été lu du ficher et
à déja été dessiner par la fonction dessiner_obstacle )

- Les fonctions privées de ce module ont pour but d'obtenir toutes les
données néssaire pour la lecture complète des données du fichier.
( déterminer le type de forme, le nombre de paramètre)


Module : t_obstacles.h
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-08
*/


/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

//le nb maximum de parametre qu'une forme peut avoir
#define MAX_PARAM 6
//pour avancer le curseur
#define POS_CUR 2

/*=========================================================*/
/*                      STRUCTURES                         */
/*=========================================================*/

typedef struct {

	// forme int pour répresenter le type de forme géométrique 
	int type_forme;

	//Le nombre d’arguments nécessaires pour dessiner cette forme (entier)
	int nb_param_forme;

	/*La liste des MAX_PARAM (= 6) arguments pour dessiner cette forme (tableau
	d’entiers)*/
	int tab_param[MAX_PARAM];

} t_obstacle;

typedef struct {
	//Le nombre d’obstacles présents (entier)
	int nb_obstacle;

	//Un tableau dynamique d’obstacles (pointeur à des « t_obstacle »)
	t_obstacle * tab_obstacles;

} t_liste_obs;



/********************************************************************/
/*						DECLARATIONS DES FONCTIONS					*/
/********************************************************************/

/*
LIRE_OBSTACLES
Codée par Youssef Soliman, Hugo Belin

Cette fonction reçoit le nom du fichier à lire et va récupérer 
toutes les informations de l'obstacle.

PARAMÈTRES :
-nom_fich :  (type : char *) 
-obstacles : (type : t_liste_obs *) 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int) le nombre de points

*/
int lire_obstacles(char *nom_fich, t_liste_obs *obstacles);


/*
DESSINER_OBSTACLES
Codée par Youssef Soliman, Hugo Belin 

Cette fonction reçois la liste d'obstacle et va dessiner chaque forme 
géométrique de cette liste.

PARAMÈTRES :
-obstacles : (type : const t_liste_obs *) liste d'obtacle 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Aucune (void).
*/
void dessiner_obstacles(const t_liste_obs * obstacles);

/*
DETRUIRE_OBSTACLES
Codée par Youssef Soliman, Hugo Belin

Cette fonction détruit la liste d'obstacle qui à été lu du ficher et 
à déja été dessiner par la fonction dessiner_obstacle 

PARAMÈTRES :
-obstacles : (type : t_liste_obs *) liste d'obstacle 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Aucune (void).
*/
void detruire_obstacles(t_liste_obs * obstacles);


/*******************************************************************************/