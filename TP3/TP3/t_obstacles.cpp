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

#include "mode_graphique.h"
#include "t_obstacles.h"


/*********************************************************/
/*         DECLARATIONS DES FONCTIONS PRIVÉES            */
/*********************************************************/


/*****************************************************/
/*****************************************************/
// FONCTIONS INFORMATRICES

/*
GET_TYPE_FORMES
Codée par Youssef Soliman, Hugo Belin

Cette fonction donne l'équvalent enum de la forme géométrique
lu dans le fichier qui est une lettre (char)

PARAMÈTRES :
-code : lettre representant la forme géométrique (type : char)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: le type constant (enum) de la forme(type: int).

*/
static int get_type_formes(char code);


/*
GET_NB_PARAM

Codée par Youssef Soliman, Hugo Belin

Cette fonction donne le nombre de paramètre que chaque forme géométrique
doit avoir pour être dessiné

PARAMÈTRES :
-forme : (type : int) l'enum de la forme geométrique

HYPOTHESES: Aucune.

VALEUR DE RETOUR: (type: int) le nombre de paramètre de la forme geométrique
*/
static int get_nb_param(int forme);


/*
GET_PARAM_LIGNE
Codée par Youssef Soliman, Hugo Belin

Cette fonction va chercher dans le fichier tous les paramètre nécéssaire pour
dessiner la forme désirée dans chaque ligne de texte contenant les données des
obstacles.

PARAMÈTRES :
-ptr_fichier : le fichier texte (type : FILE * )
-obstacle : la structure d'un obstacle (type : t_obstacle *)

HYPOTHESES: Aucune.

VALEUR DE RETOUR: Aucune.
*/
static void get_param_ligne(FILE * ptr_fichier, t_obstacle * obstacle);



/*********************************************************/
/*          DEFINITIONS DES FONCTIONS PRIVÉES            */
/*********************************************************/

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

static int get_nb_param(int forme) {
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

//-------------------------------------------------------------------

static void get_param_ligne(FILE * ptr_fichier, t_obstacle * obstacle) {
	int i = 0;

	/*continue la lecture d'une ligne tant qu'on est pas arriver
	a la fin de la ligne*/
	while (fgetc(ptr_fichier) != '\n') {
		fscanf(ptr_fichier, "%i", &obstacle->tab_param[i]);
		i++;
	}
}



/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

//-------------------------------------------------------------------

int lire_obstacles(char * nom_fich, t_liste_obs * obstacles) {
	//Iterateur
	int i;
	//le nombre de points contenus dans le trajet normalisé
	int nb_points = 0;

	//Pointeur vers le fichier a lire.
	FILE * ptr_fichier;

	//On ouvre le fichier en mode lecture texte
	ptr_fichier = fopen(nom_fich, "rt");

	//La fonction tente d’ouvrir le fichier texte(en cas d’echec on retourne 0)
	if (ptr_fichier == NULL) {
		printf("Impossible d'ouvrir le fichier %s.\n", nom_fich);
		fclose(ptr_fichier);
		return 0;
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
		return 0;
	}

	//avancer le curseur a la prochaine ligne
	fseek(ptr_fichier, POS_CUR, SEEK_CUR);

	//pour chaque ligne d'obstacles
	for (i = 0; i < obstacles->nb_obstacle; i++) {

		//obtient le type de forme
		obstacles->tab_obstacles[i].type_forme = 
			get_type_formes(fgetc(ptr_fichier));

		//obtient le nb de parametres
		obstacles->tab_obstacles[i].nb_param_forme = 
			get_nb_param(obstacles->tab_obstacles[i].type_forme);

		//obtient les parametres pour chaque formes
		get_param_ligne(ptr_fichier, &obstacles->tab_obstacles[i]);

	}

	//Lit le nombre de points a la fin du fichier
	fscanf(ptr_fichier, "%i", &nb_points);

	fclose(ptr_fichier);

	return nb_points;
}

//-------------------------------------------------------------------

void dessiner_obstacles(const t_liste_obs * obstacles) {
	int i;
	int type_forme;
	int * tab_param;

	for (i = 0; i < obstacles->nb_obstacle; i++) {

		type_forme = obstacles->tab_obstacles[i].type_forme;

		/*copie du tableau de param pour evite d'ecrire la syntaxe complete
		pour chaque parametre des fonctions dessin*/
		tab_param = obstacles->tab_obstacles[i].tab_param;

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

//-------------------------------------------------------------------

void detruire_obstacles(t_liste_obs * obstacles) {
	if (obstacles->tab_obstacles != NULL) {
		obstacles->nb_obstacle = 0;
		free(obstacles->tab_obstacles);
		obstacles->tab_obstacles = NULL;
	}
}

//*****************************************************************************