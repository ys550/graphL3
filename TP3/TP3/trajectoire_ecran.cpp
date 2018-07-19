/*

Module : trajectoire_ecran.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-15
*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include "trajectoire_ecran.h"
#include "mode_graphique.h"
#include "SOURISLIB.h"

t_trajectoire_ecran init_trajectoire_ecran(void) {
	t_trajectoire_ecran file;

	file.tete = NULL;
	file.queue = NULL;
	file.nb_points = 0;

	return file;
}

int taille_trajectoire_ecran(const t_trajectoire_ecran * traj) {
	return traj->nb_points;
}

int trajectoire_ecran_vide(const t_trajectoire_ecran * traj) {
	return (traj->tete == NULL) ? 1 : 0;
}

void set_iter_debut(t_trajectoire_ecran * traj) {
	traj->ptr_iter = traj->tete;
}

/*Appleler la fonction set_iter_debut avant l'appel de cette fonction*/
t_point_ecran get_point_iter(t_trajectoire_ecran * traj) {
	t_point_ecran point_invalide;

	point_invalide.pos_x = -1;
	point_invalide.pos_y = -1;

	//Si on est pas a la fin de la liste
	if (traj->ptr_iter->suivant != NULL) {
		//avancer le pointeur au prochain noeud
		traj->ptr_iter = traj->ptr_iter->suivant;
		//obtenir le point écran du pointeur - itérateur
		return traj->ptr_iter->point;
	}

	//si le pointeur-itérateur est NULL, retour d'un point pixels non-valides
	return point_invalide;
}

int enfiler_point_ecran(t_trajectoire_ecran * traj, const t_point_ecran pt) {
	t_lien nouveau_noeud;

	//créer le nouveau noeud
	nouveau_noeud = (t_lien)malloc(sizeof(struct noeud));

	//valider l'allocation dynamique
	if (nouveau_noeud == NULL) { return NULL; }

	//attribuer la donnee pt au nouveau noeud
	nouveau_noeud->point = pt;
	//nouveau_noeud a la fin; donc aucun noeud suivant
	nouveau_noeud->suivant = NULL;

	//CAS SPÉCIAL: si la liste reçue est vide
	if (trajectoire_ecran_vide(traj)) { 
		//ce premier noeud est la tete ET la fin de liste
		traj->tete = traj->queue = nouveau_noeud;
	}
	//sinon, on va ajouter à la fin
	else {
		traj->ptr_iter = traj->queue;
		//placer le nouveau noeud a la fin
		traj->ptr_iter->suivant = nouveau_noeud;
		//déplacer la queue de liste
		traj->queue = nouveau_noeud;
	}
	//on incremente le nombre d'elements dans la file chainee
	traj->nb_points++;

	return 1;
}

int defiler_point_ecran(t_trajectoire_ecran * traj, t_point_ecran * pt) {
	
	//ne pas defiler si la file est vide
	if (trajectoire_ecran_vide(traj)) { 
		return 0; 
	}
	//si non on defile le premier noeud (tete)
	else {
		//set iter a tete
		set_iter_debut(traj);
		//on recupere le point extrait
		*pt = traj->ptr_iter->point;
		//la tete devient le noeud suivant
		traj->tete = traj->ptr_iter->suivant;
		//on libre l'espace memoire du premier noeud retire
		free(traj->ptr_iter);

		//on decremente le nombre d'elements dans la file chainee
		traj->nb_points--;

		return 1;
	}
}

int lire_trajectoire_ecran(t_trajectoire_ecran * traj) {
	//pour la position de la souris
	t_point_ecran pt;
	//le temps du delai pour capturer les evenements-souris
	int delai_ms = 1;
	int couleur;
	//0 non valide, 1 valide
	int trajet_est_valide = 1;

	//Attendre que le bouton-souris soit pesé
	attendBoutonPese();

	//Répéter:
	do {
		//Si la souris a bougée
		if (sourisBouge()) {
			//Obtenir la position de la souris
			obtientSouris(&pt.pos_x, &pt.pos_y);
			//Obtenir la couleur du pixel à cette position
			couleur = obtenir_pixel(pt.pos_x, pt.pos_y);

			//Si on ne détecte pas un OBSTACLE(bleu) ou une LIMITE(blanc)
			if (couleur != OBSTACLE && couleur != LIMITE) {
				//Afficher ce pixel en blanc
				afficher_pixel(pt.pos_x, pt.pos_y, MOYENNE);
				//Ajouter cette position à la file des points
				enfiler_point_ecran(traj, pt);
				trajet_est_valide = 1;
			}
			//Sinon
			else {
				 //On est sorti du parcours, le trajet est refusé
				afficher_texte("Trajet REFUSE! Appuyez une touche..");
				trajet_est_valide = 0;
			}

		}
		//délai(1 msec.) pour permettre de détecter les évènements - souris
		delai_ecran(delai_ms);

		//Tant que le trajet est valide ET le bouton-souris n’est pas relevé
	} while (trajet_est_valide && !boutonReleve());

	if (trajet_est_valide)
		//Retour du nombre de points saisis
		return traj->nb_points;
	else
		return 0;
}

void dessiner_trajectoire_ecran(t_trajectoire_ecran * traj, int couleur) {

}

int liberer_trajectoire_ecran(t_trajectoire_ecran * traj) {

	t_lien suivant_tempo;

	set_iter_debut(traj);

	while (traj->ptr_iter != NULL) {
		suivant_tempo = traj->ptr_iter->suivant;
		free(traj->ptr_iter);
		traj->ptr_iter = suivant_tempo;
	}

	traj->tete = NULL;
	traj->queue = NULL;

	return 0;
}

t_groupe_traj_ecran init_groupe(int taille) {

	t_groupe_traj_ecran groupe_traj;

	if (taille <= NB_TRAJECTOIRES) {
		groupe_traj.tableau_traj = (t_trajectoire_ecran *)malloc(taille *
			sizeof(t_trajectoire_ecran));
		groupe_traj.taille_tableau = taille;
		groupe_traj.nb_trajectoire = 0;
	}

	return groupe_traj;
}

int get_nombre_traj_groupe(const t_groupe_traj_ecran * groupe) {
	return groupe->nb_trajectoire;
}

int get_taille_groupe(const t_groupe_traj_ecran * groupe) {
	return groupe->taille_tableau;
}

t_trajectoire_ecran consulter_groupe(const t_groupe_traj_ecran * groupe, int position) {

	t_trajectoire_ecran traj_vide;

	if (position >= 0) {
		return groupe->tableau_traj[position];
	}
	else {
		traj_vide.nb_points = 0;
		traj_vide.ptr_iter = NULL;
		traj_vide.queue = NULL;
		traj_vide.tete = NULL;

		return traj_vide;
	}
}

int ajouter_traj_groupe(t_groupe_traj_ecran * groupe, t_trajectoire_ecran * traj) {
	
	//si le groupe n’est pas déjà plein
	if (groupe->nb_trajectoire < groupe->taille_tableau) {
		groupe->tableau_traj[groupe->nb_trajectoire] = *traj;
		groupe->nb_trajectoire++;
		return 1;
	}

	return 0;
}

int vider_traj_groupe(t_groupe_traj_ecran * groupe) {
	
	return 0;
}
