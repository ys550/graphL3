/*

Ce module fait la gestion des tableau de coordonnées t_point_plan,
les listes recu par le module t_point_plan ne sont pas de la même
longueur et seront échantillonnées à une taille normale définie dans
ce module.

Le module à pour but d'éliminer la liste de point la plus éloigniée
du trajet moyen.

Les fonction de ce module sont :

- t_liste_traj  init_trajectoire_plan(const t_groupe_traj_ecran * groupe,
int taille_norm);
( Cette fonction construit une liste de trajectoires_plan avec un
groupe de trajectoires_écran )

- t_ptr_trajet  obtenir_traj_plan(const t_liste_traj * listes_traj, int pos);
( Cette fonction localise et retourne un pointeur sur le noeud
pos du groupe de liste )

- int  trouver_traj_refuse(const t_liste_traj *listes_traj);
( Cette fonction identifie la liste à éliminer )

- void retirer_traj_refuse(t_liste_traj *listes_traj, int pos);
( Cette fonction retire la liste à éliminer )

- void ajouter_traj_moyen(t_liste_traj *listes_traj);
( Cette fonction ajoute dans l'interface graphique le trajet moyen
déterminer par la liste des trajets )

- void tranfert_plan_a_ecran(const t_ptr_trajet traj_plan,
t_trajectoire_ecran * traj_ecran);
( Cette fonction effectue le transfert des listes t_point_plan en
listes t_point_écran en arrondissant la listes de coordonnées de
chaque trajectoires pour avoir la taille normale définie )


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
Codée par Youssef Soliman, Hugo Belin

Cette fonction construit une liste de trajectoires_plan avec un 
groupe de trajectoires_écran.

PARAMÈTRES :
-groupe :  (type : t_groupe_traj_ecran *) liste de trajectoires_écran 
-taille_norm : (type : int) taille moyenne définie 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_liste_traj) liste de trajectoires_plan
*/
t_liste_traj  init_trajectoire_plan(const t_groupe_traj_ecran * groupe, 
	int taille_norm);

/*
OBTENIR_TRAJ_PLAN
Codée par Youssef Soliman, Hugo Belin

Cette fonction localise et retourne un pointeur sur le noeud 
pos du groupe de liste 

PARAMÈTRES :
-listes_traj :  (type : t_liste_traj *) liste de trajectoires
-pos : (type : int) numéro de la liste de trajectoires désirée

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_ptr_trajet) pointeur du noeud de la liste 
*/
t_ptr_trajet  obtenir_traj_plan(const t_liste_traj * listes_traj, int pos);

/*
TROUVER_TRAJ_REFUSE
Codée par Youssef Soliman, Hugo Belin

Cette fonction identifie la liste à éliminer ( la liste avec 
la liste de coordonnées la plus éloigniée du trajet moyen )

PARAMÈTRES :
-listes_traj :  (type : t_liste_traj *) liste des trajets 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int) numéro du trajet à éliminer dans la liste
*/
int  trouver_traj_refuse(const t_liste_traj *listes_traj);

/*
RETIRER_TRAJ_REFUSE
Codée par  Youssef Soliman, Hugo Belin

Cette fonction retire la liste à éliminer localiser dans la 
fonction TROUVER_TRAJ_REFUSE.

PARAMÈTRES :
-listes_traj :  (type : t_liste_traj *) liste des trajets
-pos : (type : int) numero du trajet 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien
*/
void retirer_traj_refuse(t_liste_traj *listes_traj, int pos);

/*
AJOUTER_TRAJ_MOYEN
Codée par Youssef Soliman, Hugo Belin

Cette fonction ajoute dans l'interface graphique le trajet moyen 
déterminer par la liste des trajets.

PARAMÈTRES :
-listes_traj :  (type : listes_traj *) liste des trajets 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien.
*/
void ajouter_traj_moyen(t_liste_traj *listes_traj);

/*
TRANSFERT_PLAN_A_ERCAN
Codée par Youssef Soliman, Hugo Belin

Cette fonction effectue le transfert des listes t_point_plan en 
listes t_point_écran en arrondissant la listes de coordonnées de 
chaque trajectoires pour avoir la taille normale définie.

PARAMÈTRES :
-traj_plan :  (type : t_ptr_trajet) pointeur de la liste des trajets 
-traj_ecran : (type : t_trajectoire_ecran *) liste des trajets 

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  Rien.
*/
void tranfert_plan_a_ecran(const t_ptr_trajet traj_plan,
	t_trajectoire_ecran * traj_ecran);

/*********************************************************/
/*           DECLARATIONS DES FONCTIONS PRIVÉES          */
/*********************************************************/

static t_ptr_trajet creer_nouveau_noeud(int taille_norm);

static void transferer_points(t_ptr_trajet traj_plan, 
	t_trajectoire_ecran * traj_ecran, int taille_norm);

static void enfiler_liste_traj(t_liste_traj * listes_traj, t_ptr_trajet nouveau_noeud);