/*

Module : trajectoire_plan.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-23
*/

#include <stdlib.h>
#include <stdio.h>
#include "trajectoire_plan.h"


/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

t_liste_traj init_trajectoire_plan(const t_groupe_traj_ecran * groupe, int taille_norm) {

	return t_liste_traj();
}

t_ptr_trajet obtenir_traj_plan(const t_liste_traj * listes_traj, int pos) {

	return t_ptr_trajet();
}

int trouver_traj_refuse(const t_liste_traj * listes_traj) {

	return 0;
}

void retirer_traj_refuse(t_liste_traj * listes_traj, int pos) {

}

void ajouter_traj_moyen(t_liste_traj * listes_traj) {

}

void tranfert_plan_a_ecran(const t_ptr_trajet traj_plan, t_trajectoire_ecran * traj_ecran) {

}
