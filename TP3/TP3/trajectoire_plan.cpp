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
/*           DECLARATIONS DES FONCTIONS PRIV�ES          */
/*********************************************************/

static t_ptr_trajet creer_nouveau_noeud(int taille_norm);

static void transferer_points(t_ptr_trajet traj_plan,
	t_trajectoire_ecran * traj_ecran);

static void enfiler_liste_traj(t_liste_traj * listes_traj,
	t_ptr_trajet nouveau_noeud);

static void afficher_matrice(const t_liste_traj * listes_traj,
	t_point_plan ** matrice);


/*********************************************************/
/*           DEFINITIONS DES FONCTIONS PRIV�ES           */
/*********************************************************/

/*-	cr�er un nouveau n�ud dans lequel vous allouez dynamiquement un tableau de
� taille_norm � points de type � t_point_plan � avec son pointeur-suivant
initialis� a NULL (sous-fonction priv�e). */
static t_ptr_trajet creer_nouveau_noeud(int taille_norm) {
	t_ptr_trajet nouveau_noeud;

	//cr�er le nouveau noeud
	nouveau_noeud = (t_ptr_trajet)malloc(sizeof(struct noeud_liste));

	//valider l'allocation dynamique
	if (nouveau_noeud == NULL) { return NULL; }

	nouveau_noeud->taille_tab_coor = taille_norm;

	nouveau_noeud->tab_coordonnees = (t_point_plan *)calloc(taille_norm,
		sizeof(t_point_plan));

	nouveau_noeud->suivant = NULL;

	return nouveau_noeud;
}

/*-	transf�rez les points de la file [no_file] dans le tableau dynamique du
nouveau n�ud (*).*/
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


	set_iter_debut(traj_ecran);

	//NOTE : le premier point[0] du trajet est automatiquement copi� dans le 
	//premier � t_point_plan � de la liste
	p2 = get_point_iter(traj_ecran);
	traj_plan->tab_coordonnees[pos].x = p2.pos_x;
	traj_plan->tab_coordonnees[pos].y = p2.pos_y;

	pos = 1;

	set_iter_debut(traj_ecran);
	pos_p2 = 0;
	while (pos < traj_plan->taille_tab_coor) {

		posT += inter;

		while (pos_p2 < (int)ceil(posT)) {
			p1 = p2;
			p2 = get_point_iter(traj_ecran);
			pos_p2++;
		}

		//pT  = p1 + (partie fractionnaire de T) * (p2 � p1)
		pt.x = p1.pos_x + (posT - (int)posT) * (p2.pos_x - p1.pos_x);
		pt.y = p1.pos_y + (posT - (int)posT) * (p2.pos_y - p1.pos_y);

		traj_plan->tab_coordonnees[pos] = pt;
		pos++;
	}

}


static void enfiler_liste_traj(t_liste_traj * listes_traj,
	t_ptr_trajet nouveau_noeud) {

	t_ptr_trajet ptr_iter;

	//CAS SP�CIAL: si la liste re�ue est vide
	if (listes_traj->tete == NULL) {
		//ce premier noeud est la tete ET la fin de liste
		listes_traj->tete = listes_traj->queue = nouveau_noeud;
	}
	//sinon, on va ajouter � la fin
	else {
		ptr_iter = listes_traj->queue;
		//placer le nouveau noeud a la fin
		ptr_iter->suivant = nouveau_noeud;
		//d�placer la queue de liste
		listes_traj->queue = nouveau_noeud;
	}
	//on incremente le nombre d'elements dans la file chainee
	listes_traj->nb_listes++;
}

static void afficher_matrice(const t_liste_traj * listes_traj,
	t_point_plan ** matrice) {

	int a, b;
	//pour afficher la somme des correlations de chaque colonnes
	double somme;


	printf("\nMATRICE DES CORRELATIONS:\n");
	for (a = 0; a < listes_traj->nb_listes; a++) {

		somme = 0;

		for (b = 0; b < listes_traj->nb_listes; b++) {

			printf("[%.2lf %.2lf] ", matrice[b][a].x, matrice[b][a].y);
			somme += matrice[b][a].x + matrice[b][a].y;

		}
		printf("= %.2lf\n", somme);
	}

}

/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

t_liste_traj init_trajectoire_plan(const t_groupe_traj_ecran * groupe,
	int taille_norm) {
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


	if (pos < listes_traj->nb_listes && pos >= 0) {
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
	//iterateur pour les couples de noeud A et B
	int a, b;
	int indice_col_min;
	t_ptr_trajet noeud_a;
	t_ptr_trajet noeud_b;
	t_point_plan pt_init;
	//cr�er une matrice de points-plan selon le nombre de listes dans le groupe
	t_point_plan ** matrice = creer_matrice_pts(listes_traj->nb_listes);

	pt_init.x = 1.0;
	pt_init.y = 1.0;


	//pour chaque couple de positions de n�uds (A, B)
	for (a = 0; a < listes_traj->nb_listes; a++) {

		//les cases [A, A] de la matrice doivent �tre initialis�es � [1.0, 1.0]
		matrice[a][a] = pt_init;

		//obtenir le noeud a
		noeud_a = obtenir_traj_plan(listes_traj, a);

		for (b = a + 1; b < listes_traj->nb_listes; b++) {

			//obtenir le noeud b
			noeud_b = obtenir_traj_plan(listes_traj, b);

			/*calcul de la corr�lation entre les deux listes de points contenus
			dans les n�uds A et B le resultat est inserer dans la case [A, B] 
			de la matrice*/
			matrice[a][b] = correlation_pts(noeud_a->tab_coordonnees, 
				noeud_b->tab_coordonnees, listes_traj->taille_normale);

			/*Inutile de calculer la corr�lation pour (B, A), simplement copier
			la m�me valeur dans la case [B, A]*/
			matrice[b][a] = matrice[a][b];

		}
	}
	
	/*trouver l�indice de la colonne qui a la plus petite somme de toutes ses 
	corr�lations*/
	indice_col_min = trouver_col_min(matrice, listes_traj->nb_listes);

	afficher_matrice(listes_traj, matrice);

	//d�truire la matrice de corr�lations
	detruire_matrice_pts(matrice, listes_traj->nb_listes);
	
	//retourner l�indice de la colonne minimale
	return indice_col_min;
}



void retirer_traj_refuse(t_liste_traj * listes_traj, int pos) {
	t_ptr_trajet temp;
	t_ptr_trajet noeud_precedant;

	//verifier si liste est vide
	if (listes_traj->tete == NULL)
		return;

	//Si le premier noeud (tete) est choisi
	if (pos == 0) {
		//commencer au debut
		temp = listes_traj->tete;
		//la nouvelle ref de la tete est le noeud suivant
		listes_traj->tete = temp->suivant;
	}
	//si un noeud entre le premier et le dernier (exclusif) est choisi
	else if (pos > 0 && pos < listes_traj->nb_listes - 1) {
		noeud_precedant = obtenir_traj_plan(listes_traj, (pos - 1));
		temp = noeud_precedant->suivant;
		noeud_precedant->suivant = temp->suivant;
	}
	//si le dernier noeud (queue) est choisi
	else {
		temp = listes_traj->queue;
		noeud_precedant = obtenir_traj_plan(listes_traj, (pos - 1));
		listes_traj->queue = noeud_precedant;
		listes_traj->queue->suivant = NULL;
	}

	//on supprime le tableau dans le noeud tete
	free(temp->tab_coordonnees);
	temp->taille_tab_coor = 0;
	temp->tab_coordonnees = NULL;
	//on supprime l'ancienne tete
	free(temp);
	listes_traj->nb_listes--;
}

void ajouter_traj_moyen(t_liste_traj * listes_traj) {
	int i, j;
	t_ptr_trajet nouveau_noeud;
	//le noeud courrant lors du parcours des (nb_noeuds � 1) precedant
	t_ptr_trajet noeud_courant;

	//On cr�e un nouveau n�ud
	nouveau_noeud = creer_nouveau_noeud(listes_traj->taille_normale);

	/*On traverse ensuite les (nb_noeuds � 1) n�uds pr�c�dents pour ajouter 
	chacun de leurs � taille_norm � points � la m�me position dans le tableau
	de points du nouveau n�ud*/
	for (i = 0; i < (listes_traj->nb_listes); i++) {

		noeud_courant = obtenir_traj_plan(listes_traj, i);

		/*Le nouveau n�ud contient la somme des (nb_noeuds � 1) listes 
		pr�c�dentes.*/
		for (j = 0; j < listes_traj->taille_normale; j++) {

			nouveau_noeud->tab_coordonnees[j].x += 
				noeud_courant->tab_coordonnees[j].x;

			nouveau_noeud->tab_coordonnees[j].y += 
				noeud_courant->tab_coordonnees[j].y;
		}
	}

	/*On divise chaque valeur du nouveau tableau par (nb_noeuds � 1) pour
	obtenir la moyenne des points.*/
	for (i = 0; i < listes_traj->taille_normale; i++) {
		nouveau_noeud->tab_coordonnees[i].x /= (listes_traj->nb_listes);
		nouveau_noeud->tab_coordonnees[i].y /= (listes_traj->nb_listes);
	}

	//on l'ajoute � la fin du groupe de listes
	enfiler_liste_traj(listes_traj, nouveau_noeud);
}

void tranfert_plan_a_ecran(const t_ptr_trajet traj_plan, t_trajectoire_ecran * 
	traj_ecran) {

	int i;

	set_iter_debut(traj_ecran);

	for (i = 0;  i < traj_plan->taille_tab_coor; i ++) {
		
		traj_ecran->ptr_iter->point.pos_x = 
			ARRONDIR(traj_plan->tab_coordonnees[i].x);
		
		traj_ecran->ptr_iter->point.pos_y = 
			ARRONDIR(traj_plan->tab_coordonnees[i].y);
		
		get_point_iter(traj_ecran);
	}
	
}

