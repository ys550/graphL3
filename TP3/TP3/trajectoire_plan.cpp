/*

Module : trajectoire_plan.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-23
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "trajectoire_plan.h"



/*********************************************************/
/*           DEFINITIONS DES FONCTIONS PRIVÉES           */
/*********************************************************/

/*-	créer un nouveau nœud dans lequel vous allouez dynamiquement un tableau de
« taille_norm » points de type « t_point_plan » avec son pointeur-suivant
initialisé a NULL (sous-fonction privée). */
static t_ptr_trajet creer_nouveau_noeud(int taille_norm) {
	t_ptr_trajet nouveau_noeud;

	//créer le nouveau noeud
	nouveau_noeud = (t_ptr_trajet)malloc(sizeof(struct noeud_liste));

	//valider l'allocation dynamique
	if (nouveau_noeud == NULL) { return NULL; }

	nouveau_noeud->taille_tab_coor = taille_norm;

	nouveau_noeud->tab_coordonnees = (t_point_plan *)malloc(taille_norm *
		sizeof(t_point_plan));

	nouveau_noeud->suivant = NULL;

	return nouveau_noeud;
}

/*-	transférez les points de la file [no_file] dans le tableau dynamique du
nouveau nœud (*).*/
static void transferer_points(t_ptr_trajet traj_plan,
	t_trajectoire_ecran * traj_ecran) {

	//l'intervalle d'echantillonnage
	double inter = (double)traj_ecran->nb_points / traj_plan->taille_tab_coor;
	double posT = 0;
	int pos = 0;
	int pos_p2 = 0;
	t_point_ecran p1;
	t_point_ecran p2;
	t_point_plan pt;

	//t_point_ecran = int pos_x pos_y
	//t_point_plan = double x y
	//tab_coor t_point_plan double

	set_iter_debut(traj_ecran);

	//NOTE : le premier point[0] du trajet est automatiquement copié dans le 
	//premier « t_point_plan » de la liste

	/*Tant qu'on est pas arrive au dernier noeud dans la file on traverse la
	file*/
	p2 = get_point_iter(traj_ecran);
	traj_plan->tab_coordonnees[0].x = p2.pos_x;
	traj_plan->tab_coordonnees[0].y = p2.pos_y;

	pos = 1;
	while (pos < traj_plan->taille_tab_coor) {
		//retourne t_point_ecran (pos_x,pos_y) d'un noeud de la file
		//et passe au noeud suivant

		posT += inter;

		while (pos_p2 < (int)ceil(posT)) {
			p1 = p2;
			p2 = get_point_iter(traj_ecran);
			pos_p2++;
		}

		//pT  = p1 + (partie fractionnaire de T) * (p2 – p1)
		pt.x = p1.pos_x + (posT - (int)posT) * (p2.pos_x - p1.pos_x);
		pt.y = p1.pos_y + (posT - (int)posT) * (p2.pos_y - p1.pos_y);

		//tab double
		traj_plan->tab_coordonnees[pos] = pt;
		pos++;
	}

}


/*ajoutez ce nouveau nœud à la fin de la liste de trajectoires-plan
(sous-fonction privée)*/
static void enfiler_liste_traj(t_liste_traj * listes_traj, t_ptr_trajet nouveau_noeud) {

	t_ptr_trajet ptr_iter;

	//CAS SPÉCIAL: si la liste reçue est vide
	if (listes_traj->tete == NULL) {
		//ce premier noeud est la tete ET la fin de liste
		listes_traj->tete = listes_traj->queue = nouveau_noeud;
	}
	//sinon, on va ajouter à la fin
	else {
		ptr_iter = listes_traj->queue;
		//placer le nouveau noeud a la fin
		ptr_iter->suivant = nouveau_noeud;
		//déplacer la queue de liste
		listes_traj->queue = nouveau_noeud;
	}
	//on incremente le nombre d'elements dans la file chainee
	listes_traj->nb_listes++;

}


/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

/*constructeur pour construire une liste de trajectoires-plan à partir 
d'un groupe de trajectoires-écran.  Elle reçoit un groupe de trajectoires-écran
et la taille de la normalisation des listes.*/
t_liste_traj init_trajectoire_plan(const t_groupe_traj_ecran * groupe, int taille_norm) {
	int i;
	int nb_trajet;
	t_liste_traj liste_traj;
	t_ptr_trajet nouveau_noeud;
	t_trajectoire_ecran traj;

	liste_traj.tete = NULL;
	liste_traj.queue = NULL;
	liste_traj.nb_listes = 0;
	liste_traj.taille_normale = taille_norm;

	nb_trajet = groupe->nb_trajectoire;
	
	for (i = 0; i < nb_trajet; i++) {

		nouveau_noeud  = creer_nouveau_noeud(taille_norm);
		traj = consulter_groupe(groupe, i);
		transferer_points(nouveau_noeud, &traj);
		enfiler_liste_traj(&liste_traj, nouveau_noeud);

	}

	return liste_traj;
}

t_ptr_trajet obtenir_traj_plan(const t_liste_traj * listes_traj, int pos) {
	//l'indexe du noeud courant
	int i = 0;
	t_ptr_trajet ptr_iter = listes_traj->tete;


	if (pos < listes_traj->nb_listes) {
		while (ptr_iter != NULL) {

			if (i == pos)
				return ptr_iter;

			i++;
			ptr_iter = ptr_iter->suivant;
		}
	}
	return NULL;
	
}

int trouver_traj_refuse(const t_liste_traj * listes_traj) {
	/*for (A = 0 a 5)
			for (B = A + 1 a 5)
			
			Mat A B
				B A*/
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
		temp->taille_tab_coor = 0;
		temp->tab_coordonnees = NULL;
		//on supprime l'ancienne tete
		free(temp);
		listes_traj->nb_listes--;
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

		//parcouru a la position choisi
		if (i == pos) {
			/*on assigne la ref suivant du noeud precedant le
			noeud supprime au noeud suivant le noeud supprime*/
			listes_traj->queue = temp->suivant;
			//on supprime le tableau dans le noeud choisi
			free(temp->tab_coordonnees);
			temp->tab_coordonnees = NULL;
			//On supprime le noeud choisi
			free(temp);
			listes_traj->nb_listes--;
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

