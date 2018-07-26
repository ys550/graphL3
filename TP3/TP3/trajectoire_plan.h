/*

Ce module fait la gestion des tableau de coordonn�es t_point_plan,
les listes recu par le module t_point_plan ne sont pas de la m�me
longueur et seront �chantillonn�es � une taille normale d�finie dans
ce module.

Le module � pour but d'�liminer la liste de point la plus �loigni�e
du trajet moyen.

Les fonction de ce module sont :

- t_liste_traj  init_trajectoire_plan(const t_groupe_traj_ecran * groupe,
int taille_norm);
( Cette fonction construit une liste de trajectoires_plan avec un
groupe de trajectoires_�cran )

- t_ptr_trajet  obtenir_traj_plan(const t_liste_traj * listes_traj, int pos);
( Cette fonction localise et retourne un pointeur sur le noeud
pos du groupe de liste )

- int  trouver_traj_refuse(const t_liste_traj *listes_traj);
( Cette fonction identifie la liste � �liminer )

- void retirer_traj_refuse(t_liste_traj *listes_traj, int pos);
( Cette fonction retire la liste � �liminer )

- void ajouter_traj_moyen(t_liste_traj *listes_traj);
( Cette fonction ajoute dans l'interface graphique le trajet moyen
d�terminer par la liste des trajets )

- void tranfert_plan_a_ecran(const t_ptr_trajet traj_plan,
t_trajectoire_ecran * traj_ecran);
( Cette fonction effectue le transfert des listes t_point_plan en
listes t_point_�cran en arrondissant la listes de coordonn�es de
chaque trajectoires pour avoir la taille normale d�finie )


Module : trajectoire_plan.h
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-23
*/

#include "t_point_plan.h"
#include "trajectoire_ecran.h"


/*=========================================================*/
/*                       STRUCTURES                        */
/*=========================================================*/

typedef struct noeud_liste * t_ptr_trajet;

typedef struct noeud_liste {
	int taille_tab_coor;
	t_point_plan * tab_coordonnees;
	t_ptr_trajet suivant;
} t_noeud_liste;

typedef struct {
	int nb_listes;
	int taille_normale;
	t_ptr_trajet tete;
	t_ptr_trajet queue;
} t_liste_traj;

/********************************************************************/
/*						DECLARATIONS DE FONCTIONS					*/
/********************************************************************/

/*
INIT_TRAJECTOIRE_PLAN
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction construit une liste de trajectoires_plan avec un 
groupe de trajectoires_�cran.

PARAM�TRES :
-groupe :  (type : t_groupe_traj_ecran *) liste de trajectoires_�cran 
-taille_norm : (type : int) taille moyenne d�finie 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_liste_traj) liste de trajectoires_plan
*/
t_liste_traj  init_trajectoire_plan(const t_groupe_traj_ecran * groupe, 
	int taille_norm);

/*
OBTENIR_TRAJ_PLAN
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction localise et retourne un pointeur sur le noeud 
pos du groupe de liste 

PARAM�TRES :
-listes_traj :  (type : t_liste_traj *) liste de trajectoires
-pos : (type : int) num�ro de la liste de trajectoires d�sir�e

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_ptr_trajet) pointeur du noeud de la liste 
*/
t_ptr_trajet  obtenir_traj_plan(const t_liste_traj * listes_traj, int pos);

/*
TROUVER_TRAJ_REFUSE
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction identifie la liste � �liminer ( la liste avec 
la liste de coordonn�es la plus �loigni�e du trajet moyen )

PARAM�TRES :
-listes_traj :  (type : t_liste_traj *) liste des trajets 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int) num�ro du trajet � �liminer dans la liste
*/
int  trouver_traj_refuse(const t_liste_traj *listes_traj);

/*
RETIRER_TRAJ_REFUSE
Cod�e par  Youssef Soliman, Hugo Belin

Cette fonction retire la liste � �liminer localiser dans la 
fonction TROUVER_TRAJ_REFUSE.

PARAM�TRES :
-listes_traj :  (type : t_liste_traj *) liste des trajets
-pos : (type : int) numero du trajet 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien
*/
void retirer_traj_refuse(t_liste_traj *listes_traj, int pos);

/*
AJOUTER_TRAJ_MOYEN
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction ajoute dans l'interface graphique le trajet moyen 
d�terminer par la liste des trajets.

PARAM�TRES :
-listes_traj :  (type : listes_traj *) liste des trajets 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien.
*/
void ajouter_traj_moyen(t_liste_traj *listes_traj);

/*
TRANSFERT_PLAN_A_ERCAN
Cod�e par Youssef Soliman, Hugo Belin

Cette fonction effectue le transfert des listes t_point_plan en 
listes t_point_�cran en arrondissant la listes de coordonn�es de 
chaque trajectoires pour avoir la taille normale d�finie.

PARAM�TRES :
-traj_plan :  (type : t_ptr_trajet) pointeur de la liste des trajets 
-traj_ecran : (type : t_trajectoire_ecran *) liste des trajets 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien.
*/
void tranfert_plan_a_ecran(const t_ptr_trajet traj_plan,
	t_trajectoire_ecran * traj_ecran);

/*********************************************************/
/*           DECLARATIONS DES FONCTIONS PRIV�ES          */
/*********************************************************/

static t_ptr_trajet creer_nouveau_noeud(int taille_norm);

static void transferer_points(t_ptr_trajet traj_plan, 
	t_trajectoire_ecran * traj_ecran, int taille_norm);

static void enfiler_liste_traj(t_liste_traj * listes_traj, t_ptr_trajet nouveau_noeud);