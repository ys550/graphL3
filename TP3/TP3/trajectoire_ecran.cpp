/*

Module : trajectoire_ecran.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-15
*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies à inclure 
#include "trajectoire_ecran.h"
#include "mode_graphique.h"
#include "SOURISLIB.h"

/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

//-------------------------------------------------------------------

t_trajectoire_ecran init_trajectoire_ecran(void) {
	t_trajectoire_ecran file;

	//initialiser la file de trajectoire
	file.tete = NULL;
	file.queue = NULL;
	file.ptr_iter = NULL;
	file.nb_points = 0;

	return file;
}

//-------------------------------------------------------------------

int taille_trajectoire_ecran(const t_trajectoire_ecran * traj) {
	return traj->nb_points;
}

//-------------------------------------------------------------------

int trajectoire_ecran_vide(const t_trajectoire_ecran * traj) {
	return (traj->tete == NULL) ? 1 : 0;
}

//-------------------------------------------------------------------

void set_iter_debut(t_trajectoire_ecran * traj) {
	traj->ptr_iter = traj->tete;
}

//-------------------------------------------------------------------

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

	/*retourne le point écran du pointeur itérateur
	si le pointeur-itérateur est NULL, retour d'un point pixels non-valides*/
	return point;
}

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

int defiler_point_ecran(t_trajectoire_ecran * traj, t_point_ecran * pt) {
	
	t_lien tempo;

	//ne pas defiler si la file est vide
	if (trajectoire_ecran_vide(traj)) { 
		return 0; 
	}
	//si non on defile le premier noeud (tete)
	else {
		//set iter a tete
		set_iter_debut(traj);
		//copier la reference du premier noeud dans un noeud temp
		tempo = traj->ptr_iter;
		//on recupere le point extrait
		*pt = traj->ptr_iter->point;
		//la tete devient le noeud suivant
		traj->tete = traj->ptr_iter->suivant;
		//on libre l'espace memoire du premier noeud retire
		free(tempo);

		//on decremente le nombre d'elements dans la file chainee
		traj->nb_points--;

		return 1;
	}
}

//-------------------------------------------------------------------

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
				pause_ecran();
				trajet_est_valide = 0;
			}

		}
		//délai(1 msec.) pour permettre de détecter les évènements - souris
		delai_ecran(delai_ms);

		//Tant que le trajet est valide ET le bouton-souris n’est pas relevé
	} while (trajet_est_valide && !boutonReleve());

	if (trajet_est_valide)
		//Retour du nombre de points saisis
		return taille_trajectoire_ecran(traj);
	else
		return 0;
}

//-------------------------------------------------------------------

void dessiner_trajectoire_ecran(t_trajectoire_ecran * traj, int couleur) {
	t_point_ecran pt;

	set_iter_debut(traj);

	/*Tant qu'on est pas arrive au dernier noeud dans la file on traverse la 
	file*/
	while (traj->ptr_iter != NULL) {
		//retourne t_point_ecran (pos_x,pos_y) d'un noeud de la file
		//et passe au noeud suivant
		pt = get_point_iter(traj);

		if (couleur == MOYENNE) {
			dessiner_pt(pt.pos_x, pt.pos_y, MOYENNE);
		}
		else {
			afficher_pixel(pt.pos_x, pt.pos_y, couleur);
		}

	}
}

//-------------------------------------------------------------------

int liberer_trajectoire_ecran(t_trajectoire_ecran * traj) {

	//boolean pour indique que la liste est vide
	int est_vide = 1;
	//le nombre de noeuds supprimés
	int nb_noeuds_supprime = 0;
	t_point_ecran pt;

	do {
		//retourne 0 si vide
		est_vide = defiler_point_ecran(traj, &pt);
		nb_noeuds_supprime++;
	} while (est_vide != 0);
	
	traj->tete = NULL;
	traj->queue = NULL;

	return nb_noeuds_supprime;
}

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

int get_nombre_traj_groupe(const t_groupe_traj_ecran * groupe) {
	return groupe->nb_trajectoire;
}

//-------------------------------------------------------------------

int get_taille_groupe(const t_groupe_traj_ecran * groupe) {
	return groupe->taille_tableau;
}

//-------------------------------------------------------------------

t_trajectoire_ecran consulter_groupe(const t_groupe_traj_ecran * groupe, 
	int position) {

	t_trajectoire_ecran traj_vide;

	//si la position est valide
	if (position >= 0 && position < get_taille_groupe(groupe)) {
		//retourne le trajet
		return groupe->tableau_traj[position];
	}
	//si non retourne un trajet vide
	else {
		traj_vide.nb_points = 0;
		traj_vide.ptr_iter = NULL;
		traj_vide.queue = NULL;
		traj_vide.tete = NULL;

		return traj_vide;
	}
}

//-------------------------------------------------------------------

int ajouter_traj_groupe(t_groupe_traj_ecran * groupe,
	t_trajectoire_ecran * traj) {

	//indexe pour # trajectoire
	int no_traj = 0;
	
	//si le groupe n’est pas déjà plein
	if (get_nombre_traj_groupe(groupe) < get_taille_groupe(groupe)) {
		no_traj = get_nombre_traj_groupe(groupe);
		groupe->tableau_traj[no_traj] = *traj;
		groupe->nb_trajectoire++;
		return 1;
	}

	return 0;
}

//-------------------------------------------------------------------

int vider_traj_groupe(t_groupe_traj_ecran * groupe) {
	int i;
	//le nombre de trajectoires supprimées
	int nb_traj_supprimee = 0;

	for (i = (get_taille_groupe(groupe) - 1); i >= 0; i--) {
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
//*****************************************************************************
