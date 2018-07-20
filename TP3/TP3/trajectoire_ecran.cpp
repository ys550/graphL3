/*

Module : trajectoire_ecran.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-15
*/

//Permet de d�sactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles � inclure 
#include<stdio.h>
#include<stdlib.h>
#include "trajectoire_ecran.h"
#include "mode_graphique.h"
#include "SOURISLIB.h"

t_trajectoire_ecran init_trajectoire_ecran(void) {
	t_trajectoire_ecran file;

	file.tete = NULL;
	file.queue = NULL;
	file.ptr_iter = NULL;
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
	t_point_ecran point;

	//les points pixels non-valides
	point.pos_x = -1;
	point.pos_y = -1;

	//Si on est pas a la fin de la liste
	if (traj->ptr_iter != NULL) {
		//obtenir le point du noeud actuel
		point = traj->ptr_iter->point;
		//avancer le pointeur au prochain noeud
		traj->ptr_iter = traj->ptr_iter->suivant;
	}

	/*retourne le point �cran du pointeur it�rateur
	si le pointeur-it�rateur est NULL, retour d'un point pixels non-valides*/
	return point;
}

int enfiler_point_ecran(t_trajectoire_ecran * traj, const t_point_ecran pt) {
	t_lien nouveau_noeud;

	//cr�er le nouveau noeud
	nouveau_noeud = (t_lien)malloc(sizeof(struct noeud));

	//valider l'allocation dynamique
	if (nouveau_noeud == NULL) { return NULL; }

	//attribuer la donnee pt au nouveau noeud
	nouveau_noeud->point = pt;
	//nouveau_noeud a la fin; donc aucun noeud suivant
	nouveau_noeud->suivant = NULL;

	//CAS SP�CIAL: si la liste re�ue est vide
	if (trajectoire_ecran_vide(traj)) { 
		//ce premier noeud est la tete ET la fin de liste
		traj->tete = traj->queue = nouveau_noeud;
	}
	//sinon, on va ajouter � la fin
	else {
		traj->ptr_iter = traj->queue;
		//placer le nouveau noeud a la fin
		traj->ptr_iter->suivant = nouveau_noeud;
		//d�placer la queue de liste
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

	//Attendre que le bouton-souris soit pes�
	attendBoutonPese();

	//R�p�ter:
	do {
		//Si la souris a boug�e
		if (sourisBouge()) {
			//Obtenir la position de la souris
			obtientSouris(&pt.pos_x, &pt.pos_y);
			//Obtenir la couleur du pixel � cette position
			couleur = obtenir_pixel(pt.pos_x, pt.pos_y);

			//Si on ne d�tecte pas un OBSTACLE(bleu) ou une LIMITE(blanc)
			if (couleur != OBSTACLE && couleur != LIMITE) {
				//Afficher ce pixel en blanc
				afficher_pixel(pt.pos_x, pt.pos_y, MOYENNE);
				//Ajouter cette position � la file des points
				enfiler_point_ecran(traj, pt);
				trajet_est_valide = 1;
			}
			//Sinon
			else {
				 //On est sorti du parcours, le trajet est refus�
				afficher_texte("Trajet REFUSE! Appuyez une touche..");
				trajet_est_valide = 0;
			}

		}
		//d�lai(1 msec.) pour permettre de d�tecter les �v�nements - souris
		delai_ecran(delai_ms);

		//Tant que le trajet est valide ET le bouton-souris n�est pas relev�
	} while (trajet_est_valide && !boutonReleve());

	if (trajet_est_valide)
		//Retour du nombre de points saisis
		return traj->nb_points;
	else
		return 0;
}
/*
dessiner une  trajectoire dans l'�cran graphique
utiliser mode_graphique.h pour le r�aliser

PARAMETRES : l'adresse de la trajectoire, la couleur d'affichage d�sir�e

SORTIE: Rien
*/
void dessiner_trajectoire_ecran(t_trajectoire_ecran * traj, int couleur) {
	/*fonction pour afficher tous les points d�une trajectoire.  Elle re�oit la 
	couleur d�affichage d�sir�e en deuxi�me param�tre.  C�est ici que vous 
	utilisez les fonctions � set_iter_debut() � et � get_point_iter() �. 
	On place l�it�rateur au d�but de la file et pour tous les points de la file,
	on r�cup�re le point de la position-courante pour ensuite l�afficher.  
	Notez que l�on ne doit PAS �liminer les n�uds ici, on faire juste les consulter.
	NOTE : si la couleur re�ue en param�tre est MOYENNE (blanc), vous devez utiliser la
	fonction � dessiner_pt � (pour afficher le trajet-moyen), autrement on utilise 
	� afficher_pixel() �.
	*/
	t_point_ecran pt;

	set_iter_debut(traj);

	while (traj->ptr_iter != NULL) {
		//retourne t_point_ecran (pos_x,pos_y)
		pt = get_point_iter(traj);
	}
	




}

int liberer_trajectoire_ecran(t_trajectoire_ecran * traj) {

	t_lien tempo;
	//le nombre de noeuds supprim�s
	int nb_noeuds_supprime = 0;

	set_iter_debut(traj);

	while (traj->ptr_iter != NULL) {
		tempo = traj->ptr_iter;
		traj->ptr_iter = traj->ptr_iter->suivant;
		free(tempo);
		nb_noeuds_supprime++;
	}

	traj->tete = NULL;
	traj->queue = NULL;

	return nb_noeuds_supprime;
}

t_groupe_traj_ecran init_groupe(int taille) {

	t_groupe_traj_ecran groupe_traj;

	//ne permet pas d'avoir une taille plus grande que la constante defini
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

	if (position >= 0 && position < groupe->taille_tableau) {
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
	
	//si le groupe n�est pas d�j� plein
	if (groupe->nb_trajectoire < groupe->taille_tableau) {
		groupe->tableau_traj[groupe->nb_trajectoire] = *traj;
		groupe->nb_trajectoire++;
		return 1;
	}

	return 0;
}

int vider_traj_groupe(t_groupe_traj_ecran * groupe) {
	int i;
	//le nombre de trajectoires supprim�es
	int nb_traj_supprimee = 0;

	for (i = groupe->taille_tableau - 1; i >= 0; i--) {
		/*Si la fonction liberer_trajectoire_ecran retourne 0 noeuds supprime,
		il n'y avait donc pas de trajectoire dans l'indexe i du tableau_traj*/
		if (liberer_trajectoire_ecran(&groupe->tableau_traj[i])) {
			nb_traj_supprimee++;
		}
	}
	free(groupe->tableau_traj);
	groupe->nb_trajectoire = 0;
	groupe->taille_tableau = 0;
	groupe->tableau_traj = NULL;

	return nb_traj_supprimee;
}
