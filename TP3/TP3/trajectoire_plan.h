/*

Module : trajectoire_plan.h
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-23
*/
#include "t_point_plan.h"
#include "trajectoire_ecran.h"
/*=========================================================*/
/*                       STRUCTURES                         */
/*=========================================================*/

typedef struct noeud_liste * t_ptr_trajet;

typedef struct noeud_liste {
	int taille_tab_coor;
	t_point_plan * tab_coordonnees;
	t_ptr_trajet suivant;
} t_noeud_liste;

typedef struct {
	int nb_listes;
	int taille_liste;
	t_ptr_trajet tete;
	t_ptr_trajet queue;
	t_ptr_trajet ptr_iter;
} t_liste_traj;

/********************************************************************/
/*						DECLARATIONS DE FONCTIONS					*/
/********************************************************************/

/*
INIT_TRAJECTOIRE_PLAN
Codée par

Cette fonction

PARAMÈTRES :
-groupe :  (type : t_groupe_traj_ecran *)
-taille_norm : (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_liste_traj).

EXEMPLES D'APPEL :
-
-
*/
t_liste_traj  init_trajectoire_plan(const t_groupe_traj_ecran * groupe, int taille_norm);

/*
OBTENIR_TRAJ_PLAN
Codée par

Cette fonction

PARAMÈTRES :
-listes_traj :  (type : t_liste_traj *)
-pos : (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_ptr_trajet).

EXEMPLES D'APPEL :
-
-
*/
t_ptr_trajet  obtenir_traj_plan(const t_liste_traj * listes_traj, int pos);

/*
TROUVER_TRAJ_REFUSE
Codée par

Cette fonction

PARAMÈTRES :
-listes_traj :  (type : t_liste_traj *)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int).

EXEMPLES D'APPEL :
-
-
*/
int  trouver_traj_refuse(const t_liste_traj *listes_traj);

/*
RETIRER_TRAJ_REFUSE
Codée par

Cette fonction

PARAMÈTRES :
-listes_traj :  (type : t_liste_traj *)
-pos : (type : int

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien

EXEMPLES D'APPEL :
-
-
*/
void retirer_traj_refuse(t_liste_traj *listes_traj, int pos);

/*
AJOUTER_TRAJ_MOYEN
Codée par

Cette fonction

PARAMÈTRES :
-listes_traj :  (type : listes_traj *)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien.

EXEMPLES D'APPEL :
-
-
*/
void ajouter_traj_moyen(t_liste_traj *listes_traj);

/*
TRANSFERT_PLAN_A_ERCAN
Codée par

Cette fonction

PARAMÈTRES :
-traj_plan :  (type : t_ptr_trajet)
-traj_ecran : (type : t_trajectoire_ecran *)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien.

EXEMPLES D'APPEL :
-
-
*/
void tranfert_plan_a_ecran(const t_ptr_trajet traj_plan, t_trajectoire_ecran * traj_ecran);