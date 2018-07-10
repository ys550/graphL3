/*

Module : t_obstacles.h
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-08
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

/*pour afficher les resultat des variables de la struct lors des tests de la 
fonction lire_obstacle*/
#define TEST_OBSTACLE 1

/*=========================================================*/
/*                      STRUCTURES                         */
/*=========================================================*/

typedef struct {

	/*Un code num�rique repr�sentant le type de forme (entier).  Il existe 6
	types de formes pouvant �tre dessin�s par ce module, leurs codes sont
	�num�r�s (avec � enum �) dans le fichier-interface du module
	�mode_graphique�.*/
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

/**********COMMENTAIRE COPIER/COLLER DE L'ENONCE A SUPPRIMER*******************
Cette proc�dure re�oit une liste d�obstacles d�j� initialis�e et va dessiner
chaque forme contenue dans la liste.  Le � code � de la forme vous permet de
choisir la bonne proc�dure � appeler pour chaque forme.  Les param�tres sont
toujours fournis � partir du tableau d�arguments de chaque � t_obstacle � en
ordre de gauche � droite (de [0] � [nb_param- 1] dans le tableau).  Notez que
la couleur bleue (pour repr�senter de l�eau) a d�j� �t� attribu�e � toutes les
formes sauf la forme PT. La proc�dure qui dessine cette forme re�oit donc la
valeur de la couleur en 3i�me param�tre.
******************************************************************************/
/*
LIRE_OBSTACLES
Cod�e par

Cette fonction

PARAM�TRES :
-nom_fich :  (type : char *)
-obstacles : (type : t_liste_obs *)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int).

EXEMPLES D'APPEL :
-
-
*/
int lire_obstacles(char *nom_fich, t_liste_obs *obstacles);



/**********COMMENTAIRE COPIER/COLLER DE L'ENONCE A SUPPRIMER*******************
Cette proc�dure re�oit une liste d�obstacles d�j� initialis�e et va dessiner
chaque forme contenue dans la liste.  Le � code � de la forme vous permet de
choisir la bonne proc�dure � appeler pour chaque forme.  Les param�tres sont
toujours fournis � partir du tableau d�arguments de chaque � t_obstacle � en
ordre de gauche � droite (de [0] � [nb_param- 1] dans le tableau).  Notez que
la couleur bleue (pour repr�senter de l�eau) a d�j� �t� attribu�e � toutes les
formes sauf la forme PT. La proc�dure qui dessine cette forme re�oit donc la
valeur de la couleur en 3i�me param�tre.
******************************************************************************/
/*
DESSINER_OBSTACLES
Cod�e par

Cette fonction

PARAM�TRES :
-obstacles : (type : const t_liste_obs *)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Aucune (void).

EXEMPLES D'APPEL :
-
-
*/
void dessiner_obstacles(const t_liste_obs * obstacles);


/**********COMMENTAIRE COPIER/COLLER DE L'ENONCE A SUPPRIMER*******************
Proc�dure pour lib�rer l�allocation dynamique du tableau d�obstacles de la
liste re�ue et remettre son nombre d�obstacles � z�ro.
******************************************************************************/
/*
DETRUIRE_OBSTACLES
Cod�e par

Cette fonction

PARAM�TRES :
-obstacles : (type : t_liste_obs *)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Aucune (void).

EXEMPLES D'APPEL :
-
-
*/
void detruire_obstacles(t_liste_obs * obstacles);

/*
GET_TYPE_FORMES
Cod�e par

Cette fonction

PARAM�TRES :
-code : (type : char)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: le type constant (enum) de la forme(type: int).

EXEMPLES D'APPEL :
-
-
*/
static int get_type_formes(char code);

/*
GET_NB_PARAM_FORME
Cod�e par

Cette fonction

PARAM�TRES :
-forme : (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: le type en entier de la forme(type: int).

EXEMPLES D'APPEL :
-
-
*/
static int get_nb_param_forme(int forme);

/*
GET_PARAM_LIGNE
Cod�e par

Cette fonction

PARAM�TRES :
-type_forme : (type : int)
-tab_param : (type : int)
-param_fichier : (type : char *)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: Aucune.

EXEMPLES D'APPEL :
-
-
*/
static void get_param_ligne(int type_forme, int * tab_param, char * param_fichier);

char * int_a_char(int entier);

/*******************************************************************************/