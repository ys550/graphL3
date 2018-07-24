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
	//pour la position du noeud lorsqu'on ne choisi pas le premier (pos:0)
	int i = 1;
	t_ptr_trajet temp;

	//verifier si liste est vide
	if (listes_traj->tete == NULL)
		return;

	//commencer au debut
	temp = listes_traj->tete;

	//Si on choisi le premier noeud (tete)
	if (pos == 0) {
		//la nouvelle ref de la tete est le noeud suivant
		listes_traj->tete = temp->suivant;
		//on supprime le tableau dans le noeud tete
		free(temp->tab_coordonnees);
		temp->tab_coordonnees = NULL;
		//on supprime l'ancienne tete
		free(temp);
		return;
	}

	/*Si non; si on choisi une autre position: la reference de la tete reste la
	meme, mais la ref de la queue peut change*/

	//on assigne la queue de nouveau: on commence par le debut
	listes_traj->queue = listes_traj->tete;

	/*On traverse la liste jusqu'a la fin: temp et queue avance en meme temps.
	 Les deux commencent par la tete
	*/
	while (temp->suivant != NULL) {

		//parcourir la liste avec temp
		temp = temp->suivant;

		//on a parcouru la liste jusqu'au noeud a la position choisi
		if (i == pos) {
			/*on assigne la ref suivant du noeud precedant(queue temporaire) le
			noeud supprime au noeud suivant le noeud supprime*/
			listes_traj->queue = temp->suivant;
			//on supprime le tableau dans le noeud choisi
			free(temp->tab_coordonnees);
			temp->tab_coordonnees = NULL;
			//On supprime le noeud choisi
			free(temp);
			return;
		}
		
		/*
		 on reassigne la referance de la queue au prochain noeud jusqu'a ce
		 qu'on arrive au vrai dernier noeud change au cas que la queue a ete 
		 change/supprime
		*/
		listes_traj->queue = listes_traj->queue->suivant;

		//incremente la position du noeud courrant
		i++;
	}
}

void ajouter_traj_moyen(t_liste_traj * listes_traj) {

}

void tranfert_plan_a_ecran(const t_ptr_trajet traj_plan, t_trajectoire_ecran * traj_ecran) {

}
