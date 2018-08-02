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
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

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

	//avancer le curseur a la prochaine ligne
	fseek(ptr_fichier, POS_CUR, SEEK_CUR);

	//pour chaque ligne d'obstacles
	for (i = 0; i < obstacles->nb_obstacle; i++) {

		//obtient le type de forme
		obstacles->tab_obstacles[i].type_forme = 
			get_type_formes(fgetc(ptr_fichier));

		//obtient les parametres pour chaque formes
		get_param_ligne(ptr_fichier, &obstacles->tab_obstacles[i]);

	}

	//Lit le nombre de points a la fin du fichier
	fscanf(ptr_fichier, "%i", &nb_points);

	fclose(ptr_fichier);

	return nb_points;
}

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

void detruire_obstacles(t_liste_obs * obstacles) {
	if (obstacles->tab_obstacles != NULL) {
		obstacles->nb_obstacle = 0;
		free(obstacles->tab_obstacles);
		obstacles->tab_obstacles = NULL;
	}
}

/*********************************************************/
/*          DEFINITIONS DES FONCTIONS PRIVÉES            */
/*********************************************************/

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


static void get_param_ligne(FILE * ptr_fichier, t_obstacle * obstacle) {
	int i = 0;

	while (fgetc(ptr_fichier) != '\n') {
		fscanf(ptr_fichier, "%i", &obstacle->tab_param[i]);
		obstacle->nb_param_forme++;
		i++;
	}
}