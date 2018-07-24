/*

Module : t_obstacles.h
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-08
*/

/* 

Ce module � pour but de dessiner dans le mode graphique les 
obstacles ( forme g�om�trique ).

Les informations des formes g�om�triques sont contenues dans des 
fichers textes qui seront lus et utilis�es dans dans les fonctions
de ce module.

Les fonctions utilis�es ( lectures des donn�es, cr�ation du mode graphique,
cr�ation du parcours avec la cr�ation des formes g�om�trique) :

- int lire_obstacles(char *nom_fich, t_liste_obs *obstacles);
  ( Cette fonction re�oit le nom du fichier � lire et va r�cup�rer 
    toutes les informations de l'obstacle )

- void dessiner_obstacles(const t_liste_obs * obstacles);
  ( Cette fonction re�ois la liste d'obstacle et va dessiner chaque forme 
    g�om�trique de cette liste )

- void detruire_obstacles(t_liste_obs * obstacles);
  ( Cette fonction d�truit la liste d'obstacle qui � �t� lu du ficher et 
    � d�ja �t� dessiner par la fonction dessiner_obstacle )

- Les fonctions priv�es de ce module ont pour but d'obtenir toutes les 
  donn�es n�ssaire pour la lecture compl�te des donn�es du fichier.
  ( d�terminer le type de forme, le nombre de param�tre) 



*/












/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

//le nb maximum de parametre qu'une forme peut avoir
#define MAX_PARAM 6

//le nb de parametre pour dessiner chaque formes
#define NB_PARAM_PT 3
#define NB_PARAM_CERCLE 3
#define NB_PARAM_ELLIPSE 4
#define NB_PARAM_LIGNE 4
#define NB_PARAM_RECTANGLE 4
#define NB_PARAM_TRIANGLE 6

//la longeur max de char d'une ligne dans le fichier
#define LONGUEUR_LIGNE 100

//la premiere ligne des obstacles
#define LIGNE_DEBUT_OBSTACLE 1
//la derniere ligne contenant les obstacles
#define LIGNE_OBS_FIN 1
//la position du curseur sur une ligne d'obstacle suivant le code
#define POS_FIN_CODE 1
//pour placer le curseur au debut
#define CUR_DEBUT 0
//pour place le curseur au debut du premier parametre d'une ligne d'obstacle
#define CUR_DEBUT_OBSTACLE 3


/*=========================================================*/
/*                      STRUCTURES                         */
/*=========================================================*/

typedef struct {

	// forme int pour r�presenter le type de forme g�om�trique 
	int type_forme;

	//Le nombre d�arguments n�cessaires pour dessiner cette forme (entier)
	int nb_param_forme;

	/*La liste des MAX_PARAM (= 6) arguments pour dessiner cette forme (tableau
	d�entiers)*/
	int tab_param[MAX_PARAM];

} t_obstacle;

typedef struct {
	//Le nombre d�obstacles pr�sents (entier)
	int nb_obstacle;

	//Un tableau dynamique d�obstacles (pointeur � des � t_obstacle �)
	t_obstacle * tab_obstacles;

} t_liste_obs;



/********************************************************************/
/*						DECLARATIONS DES FONCTIONS					*/
/********************************************************************/

/*
LIRE_OBSTACLES
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction re�oit le nom du fichier � lire et va r�cup�rer 
toutes les informations de l'obstacle.

PARAM�TRES :
-nom_fich :  (type : char *) 
-obstacles : (type : t_liste_obs *) 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int) echec 0 , au sinon 1

*/
int lire_obstacles(char *nom_fich, t_liste_obs *obstacles);


/*
DESSINER_OBSTACLES
Cod�e par Youssef Soliman, Hugo Belin 

Cette fonction re�ois la liste d'obstacle et va dessiner chaque forme 
g�om�trique de cette liste.

PARAM�TRES :
-obstacles : (type : const t_liste_obs *) liste d'obtacle 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Aucune (void).
*/
void dessiner_obstacles(const t_liste_obs * obstacles);

/*
DETRUIRE_OBSTACLES
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction d�truit la liste d'obstacle qui � �t� lu du ficher et 
� d�ja �t� dessiner par la fonction dessiner_obstacle 

PARAM�TRES :
-obstacles : (type : t_liste_obs *) liste d'obstacle 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Aucune (void).
*/
void detruire_obstacles(t_liste_obs * obstacles);

/*****************************************************/
/*****************************************************/
// TROIS FONCTIONS INFORMATRICES

/*
GET_TYPE_FORMES
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction donne l'�quvalent enum de la forme g�om�trique 
lu dans le fichier qui est une lettre (char)

PARAM�TRES :
-code : (type : char) lettre representant la forme g�om�trique

HYPOTHESES: Aucune.

VALEUR DE RETOUR: le type constant (enum) de la forme(type: int).

*/
static int get_type_formes(char code);

/*
GET_NB_PARAM_FORME
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction donne le nombre de param�tre que chaque forme g�om�trique 
doit avoir pour �tre dessin�e.

PARAM�TRES :
-forme : (type : int) l'enum de la forme g�om�trique 

HYPOTHESES: Aucune.

VALEUR DE RETOUR: (type: int) le nombre de param�tre de la forme g�om�trique
*/
static int get_nb_param_forme(int forme);

/*
GET_PARAM_LIGNE
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction va chercher dans le fichier tous les param�tre n�c�ssaire pour 
dessiner la forme d�sir�e

PARAM�TRES :
-type_forme : (type : int) enum de la forme 
-tab_param : (type : int) le nombre de param�tre de la forme 
-param_fichier : (type : char *) le nom du fichier

HYPOTHESES: Aucune.

VALEUR DE RETOUR: Aucune.
*/
static void get_param_ligne(int type_forme, int * tab_param, char * param_fichier);


/*******************************************************************************/