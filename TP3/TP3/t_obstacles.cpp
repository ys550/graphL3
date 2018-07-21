/*

Module : t_obstacles.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-08
*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"winBGIm.h"
#include "mode_graphique.h"
#include "t_obstacles.h"


/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

int lire_obstacles(char * nom_fich, t_liste_obs * obstacles) {
	//Iterateur
	int i = 0, j;
	/*le numero des lignes contenant les donnees de obstacles*/
	int no_ligne = LIGNE_DEBUT_OBSTACLE;
	//le nombre de points contenus dans le trajet normalisé
	int nb_points = 0;
	//pour le contenue d'une seule ligne dans le fichier
	char tab_ligne_unique_param[LONGUEUR_LIGNE];

	//Pointeur vers le fichier a lire.
	FILE * ptr_fichier;

	//On ouvre le fichier en mode lecture texte
	ptr_fichier = fopen(nom_fich, "rt");

	//La fonction tente d’ouvrir le fichier texte(en cas d’echec on retourne 0)
	if (ptr_fichier == NULL) {
		printf("Impossible d'ouvrir le fichier %s.\n", nom_fich);
		fclose(ptr_fichier);
		return EXIT_FAILURE;
	}


	/*On lit le nombre d'obstacle et place le curseur apres le nombre*/
	fscanf(ptr_fichier, "%i", &obstacles->nb_obstacle);


	/*utiliser le nb d'obstacle pour l’allocation dynamique de la liste
	d’obstacles*/
	obstacles->tab_obstacles = (t_obstacle *)malloc(obstacles->nb_obstacle *
		sizeof(t_obstacle));

	//en cas d’échec on ferme le fichier et on retourne 0
	if (obstacles->tab_obstacles == NULL) {
		printf("Echec d'allocation de memoire pour le tableau d'obstacles.\n");
		fclose(ptr_fichier);
		return EXIT_FAILURE;
	}

	/*Cette boucle determine le type de forme sur chaque ligne d'obstacle et sont
	nombre de parametre*/
	while (!feof(ptr_fichier)) {

		fgets(tab_ligne_unique_param, LONGUEUR_LIGNE, ptr_fichier);

		if (no_ligne < obstacles->nb_obstacle + LIGNE_OBS_FIN) {
			obstacles->tab_obstacles[i].type_forme =
				get_type_formes(fgetc(ptr_fichier));
			obstacles->tab_obstacles[i].nb_param_forme =
				get_nb_param_forme(obstacles->tab_obstacles[i].type_forme);
			no_ligne++;
		}

		i++;
	}

	/*le numero de ligne contenant les donnees du premier obstacle:
	On revient au premier obstacle pour lire les parametres de chaque 
	obstacles*/
	no_ligne = LIGNE_DEBUT_OBSTACLE;
	i = 0;
	/*On remet le curseur de lecture du fichier ptr_fichier au debut du des
	donnees du premier obstacle*/
	fseek(ptr_fichier, CUR_DEBUT, SEEK_SET);
	/*On relit le nombre d'obstacle pour placer le curseur apres le nombre
	d'obstacle*/
	fscanf(ptr_fichier, "%i", &obstacles->nb_obstacle);
	//On avance le curseur de 3 de la position courante du curseur
	fseek(ptr_fichier, CUR_DEBUT_OBSTACLE, SEEK_CUR);
	
	/*Cette boucle vas chercher chacun des parametres pour chaque obstacles*/
	while (no_ligne < obstacles->nb_obstacle + LIGNE_OBS_FIN) {

		//Avancer le curseur de 1 apres le code de type_forme
		fseek(ptr_fichier, POS_FIN_CODE, SEEK_CUR);

		/*Prendre seulement les parametres des obstacles sans le code au debut
		de la ligne et les insere dans le tableau tab_ligne_unique_param*/
		fgets(tab_ligne_unique_param, LONGUEUR_LIGNE, ptr_fichier);

		/*separe et insere les donnes individuel de parametre du tableau 
		tab_ligne_unique_param dans le tableau tab_param*/
		get_param_ligne(obstacles->tab_obstacles[i].type_forme,
			obstacles->tab_obstacles[i].tab_param, tab_ligne_unique_param);
		i++;
		no_ligne++;
	}

	//Lit le nombre de points a la fin du fichier
	fscanf(ptr_fichier, "%i", &nb_points);

	fclose(ptr_fichier);

	return nb_points;
}

void dessiner_obstacles(const t_liste_obs * obstacles) {
	int i, j;
	int type_forme;
	int tab_param[MAX_PARAM];

	for (i = 0; i < obstacles->nb_obstacle; i++) {

		type_forme = obstacles->tab_obstacles[i].type_forme;

		/*copie du tableau de param pour evite d'ecrire la syntaxe complete 
		pour chaque parametre des fonctions dessin*/
		for (j = 0; j < obstacles->tab_obstacles[i].nb_param_forme; j++) {
			tab_param[j] = obstacles->tab_obstacles[i].tab_param[j];
		}

		switch (type_forme) {
		case PT:
			dessiner_pt(tab_param[0], tab_param[1], tab_param[2]);
			break;
		case CERCLE:
			dessiner_cercle(tab_param[0], tab_param[1], tab_param[2]);
			break;
		case ELLIPSE:
			dessiner_ellipse(tab_param[0], tab_param[1], tab_param[2],
				tab_param[3]);
			break;
		case LIGNE:
			dessiner_ligne(tab_param[0], tab_param[1], tab_param[2],
				tab_param[3]);
			break;
		case RECTANGLE:
			dessiner_rect(tab_param[0], tab_param[1], tab_param[2],
				tab_param[3]);
			break;
		case TRIANGLE:
			dessiner_tri(tab_param[0], tab_param[1], tab_param[2], tab_param[3],
				tab_param[4], tab_param[5]);
			break;
		}

	}

}

void detruire_obstacles(t_liste_obs * obstacles) {
	if (obstacles->tab_obstacles != NULL) {
		obstacles->nb_obstacle = 0;
		free(obstacles->tab_obstacles);
		obstacles->tab_obstacles = NULL;
	}
}

static int get_type_formes(char code) {
	/*Les codes possibles sont: 'P', 'C', 'E', 'L', 'R' et 'T'*/
	switch (code) {
	case 'P':
		return PT;
	case 'C':
		return CERCLE;
	case 'E':
		return ELLIPSE;
	case 'L':
		return LIGNE;
	case 'R':
		return RECTANGLE;
	case 'T':
		return TRIANGLE;
	}
}

static int get_nb_param_forme(int forme) {
	switch (forme) {
	case PT:
		return NB_PARAM_PT;
	case CERCLE:
		return NB_PARAM_CERCLE;
	case ELLIPSE:
		return NB_PARAM_ELLIPSE;
	case LIGNE:
		return NB_PARAM_LIGNE;
	case RECTANGLE:
		return NB_PARAM_RECTANGLE;
	case TRIANGLE:
		return NB_PARAM_TRIANGLE;
	}
}

static void get_param_ligne(int type_forme, int * tab_param, char * param_fichier) {
	switch (type_forme) {
		case PT:
		case CERCLE:
			sscanf(param_fichier, " %d %d %d",
				&tab_param[0],
				&tab_param[1],
				&tab_param[2]);
			break;
		case ELLIPSE:
		case LIGNE:
		case RECTANGLE:
			sscanf(param_fichier, " %d %d %d %d",
				&tab_param[0],
				&tab_param[1],
				&tab_param[2],
				&tab_param[3]);
			break;
		case TRIANGLE:
			sscanf(param_fichier, " %d %d %d %d %d %d",
				&tab_param[0],
				&tab_param[1],
				&tab_param[2],
				&tab_param[3],
				&tab_param[4],
				&tab_param[5]);
			break;
	}
}
