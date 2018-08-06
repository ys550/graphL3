/*

Module : TP3_main.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-08
*/

#define _CRT_SECURE_NO_WARNINGS

// Librairies usuelles à inclure 
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>     //pour: kbhit() et _getch()

// Librairies pour les fonctions definis dans le projet
#include"winBGIm.h"
#include "mode_graphique.h"
#include "t_obstacles.h"
#include "trajectoire_ecran.h"
#include "trajectoire_plan.h"

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

//Les noms et trajets des fichiers
#define FICHIER_TRAJET_1 "trajet1.txt"
#define FICHIER_TRAJET_2 "trajet2.txt"
#define FICHIER_TRAJET_3 "trajet3.txt"
#define FICHIER_TRAJET_4 "trajet4.txt"
#define FICHIER_TRAJET_INDY "trajet_INDY.txt"

//pour repeter le mandat finale pour obtenir 2 trajet moyen successifs
#define NB_TRAJ_MOYEN 2


/********************************************************************/
/*				DECLARATIONS DES FONCTIONS PRIVÉES					*/
/********************************************************************/

static void afficher_menu();

static void choisir_option_menu(t_liste_obs * liste);

static int init_lire_formes(t_liste_obs * liste, char * nom_fich);

static t_groupe_traj_ecran affichage_traj(t_liste_obs * liste, int nb_points);

static void affichage_traj_moy_refus(t_liste_obs * liste,
	t_groupe_traj_ecran groupe_traj, int nb_points);

static void init_traj_ecran_vide(t_trajectoire_ecran * traj_ecran, 
	int taille_normale);

/*=========================================================*/
/*=========================================================*/
//Programme principal: fonction qui retourne un entier (int)
int main(void) {
	t_liste_obs liste;

	choisir_option_menu(&liste);

	return EXIT_SUCCESS;
}

/*********************************************************/
/*          DEFINITIONS DES FONCTIONS PRIVÉES            */
/*********************************************************/

//-------------------------------------------------------------------

static void afficher_menu() {
	system("cls");
	printf("Quel fichier de trajet voulez-vous?\n\n");
	printf("\t1) %s\n", FICHIER_TRAJET_1);
	printf("\t2) %s\n", FICHIER_TRAJET_2);
	printf("\t3) %s\n", FICHIER_TRAJET_3);
	printf("\t4) %s\n", FICHIER_TRAJET_4);
	printf("\t5) %s\n", FICHIER_TRAJET_INDY);
	printf("\tQ) QUITTER\n");
	printf(">");
}


//-------------------------------------------------------------------

static void choisir_option_menu(t_liste_obs * liste) {
	t_groupe_traj_ecran groupe_traj;
	unsigned char option;
	int taille_normale;
	

	do {

		afficher_menu();

		//Attente touche du clavier
		while (!_kbhit()) {}
		//retourne la touche
		option = _getch();

		switch (option) {
		case '1':
			taille_normale = init_lire_formes(liste, FICHIER_TRAJET_1);
			break;
		case '2':
			taille_normale = init_lire_formes(liste, FICHIER_TRAJET_2);
			break;
		case '3':
			taille_normale = init_lire_formes(liste, FICHIER_TRAJET_3);
			break;
		case '5':
			taille_normale = init_lire_formes(liste, FICHIER_TRAJET_INDY);
			break;
		case 'q':
		case 'Q':
			break;
		default:
			taille_normale = init_lire_formes(liste, FICHIER_TRAJET_4);
			break;
		}

		if (option != 'q' && option != 'Q') {
			groupe_traj = affichage_traj(liste, taille_normale);
			affichage_traj_moy_refus(liste, groupe_traj, taille_normale);
			detruire_obstacles(liste);
		}

	} while (option != 'q' && option != 'Q');

}


/******************************MANDAT 1************************************/
static int init_lire_formes(t_liste_obs * liste, char * nom_fich) {
	//la valeur « taille_norm » lue à la dernière ligne du fichier texte
	int nb_points;

	/*lecture du fichier texte et retour de la taille normale
	  a la fin du fichier*/
	nb_points = lire_obstacles(nom_fich, liste);

	initialiser_graphique();

	return nb_points;
}


/*************************MANDAT 2********************************/
static t_groupe_traj_ecran affichage_traj(t_liste_obs * liste, int nb_points) {
	int i;
	int nb_points_saisis;
	char msg_nb_points_saisis[100];
	char msg_dessiner[200];
	t_trajectoire_ecran traj;
	t_groupe_traj_ecran groupe_traj;
	

	//on initialise un groupe de trajectoires
	groupe_traj = init_groupe(NB_TRAJECTOIRES);

	//Avec une boucle
	do {
		
		//vous effacez l’écran
		effacer_ecran();
		//dessinez les obstacles du parcours choisi
		dessiner_obstacles(liste);
		//initialisez une variable-trajectoire
		traj = init_trajectoire_ecran();

		sprintf(msg_dessiner, "taille normalisee = %d pts. dessinez le trajet "
			"%d...", nb_points, get_nombre_traj_groupe(&groupe_traj) + 1);
		afficher_texte(msg_dessiner);

		//faites la saisie d’une trajectoire dans le parcours
		//retourne 0 lorsque la trajectoire est non-valide
		nb_points_saisis = lire_trajectoire_ecran(&traj);

		//si la trajectoire est non-valide
		if (nb_points_saisis == 0) {
			//vider cette trajectoire-écran
			liberer_trajectoire_ecran(&traj);
		}
		//si non
		else {
			//ajouter la trajectoire valide au groupe de trajectoire
			ajouter_traj_groupe(&groupe_traj, &traj);
			sprintf(msg_nb_points_saisis, "Fin de saisie de %d pts.\t Appuyez"
				" une touche..", nb_points_saisis);
			afficher_texte(msg_nb_points_saisis);
			pause_ecran();

		}

		//recommencer la saisie tant que la trajectoire est non-valide
	} while (get_nombre_traj_groupe(&groupe_traj) < NB_TRAJECTOIRES);
	
	effacer_ecran();
	dessiner_obstacles(liste);

	for (i = 0; i < groupe_traj.taille_tableau; i++) {
		traj = consulter_groupe(&groupe_traj, i);
		dessiner_trajectoire_ecran(&traj, VALIDE);
	}

	afficher_texte("Voici les trajets saisi. Appuyer une touche..");
	pause_ecran();

	return groupe_traj;
}


//*************MANDAT FINALE******************
static void affichage_traj_moy_refus(t_liste_obs * liste, 
	t_groupe_traj_ecran groupe_traj, int nb_points) {

	int i, j;
	int pos_traj_refuse;
	t_liste_traj liste_traj;
	t_ptr_trajet noeud_elimine;
	t_trajectoire_ecran traj_temp;

	/*on initialise un groupe de trajectoires-plan avec le groupe des
	trajectoires-écran et la valeur « taille_norm »*/
	liste_traj = init_trajectoire_plan(&groupe_traj, nb_points);

	/*repeter NB_TRAJ_MOYEN fois pour obetnir NB_TRAJ_MOYEN trajet 
	moyen successifs*/
	for (i = 1; i <= NB_TRAJ_MOYEN; i++) {

		//trouvez la position du trajet à éliminer du groupe
		pos_traj_refuse = trouver_traj_refuse(&liste_traj);
		//récupérez une référence à ce nœud
		noeud_elimine = obtenir_traj_plan(&liste_traj, pos_traj_refuse);
		//initialisez une trajectoire-écran vide
		init_traj_ecran_vide(&traj_temp, nb_points);
		//faites-y le transfert des points du trajet éliminé
		tranfert_plan_a_ecran(noeud_elimine, &traj_temp);
		//effacer l’écran
		effacer_ecran();
		//redessinez le parcours
		dessiner_obstacles(liste);
		//afficher le trajet éliminé avec la couleur NON_VALIDE
		dessiner_trajectoire_ecran(&traj_temp, NON_VALIDE);
		//videz la trajectoire éliminée
		liberer_trajectoire_ecran(&traj_temp);
		//retirer cette trajectoire du groupe de listes 
		retirer_traj_refuse(&liste_traj, pos_traj_refuse);

		//ajoutez-y le trajet moyen
		ajouter_traj_moyen(&liste_traj);

		for (j = 0; j < liste_traj.nb_listes; j++) {

			//initialisez une trajectoire-écran vide
			init_traj_ecran_vide(&traj_temp, nb_points);

			//faites-y le transfert des points de la trajectoire-plan #pos
			tranfert_plan_a_ecran(obtenir_traj_plan(&liste_traj, j), &traj_temp);

			if (j < liste_traj.nb_listes - 1) {
				//affichez la trajectoire - écran avec la couleur VALIDE
				dessiner_trajectoire_ecran(&traj_temp, VALIDE);
			}
			else if (j == liste_traj.nb_listes - 1) {
				//sauf la dernière qui aura la couleur MOYENNE
				dessiner_trajectoire_ecran(&traj_temp, MOYENNE);
			}
			liberer_trajectoire_ecran(&traj_temp);

		}

		afficher_texte("Voici le trajet moyen (ROUGE = trajet rejete), Appuyer une"
			" touche..");

		pause_ecran();

	}

	fermer_graphique();

}

//-------------------------------------------------------------------

static void init_traj_ecran_vide(t_trajectoire_ecran * traj_ecran, 
	int taille_normale) {

	int i;
	t_point_ecran pt_vide;

	//les points vides sont des points nulle
	pt_vide.pos_x = 0;
	pt_vide.pos_y = 0;

	//initialiser une trajectoire ecran vide
	*traj_ecran = init_trajectoire_ecran();

	//la trajectoire vide est composee de noeuds contenant des points vides
	for (i = 0; i < taille_normale; i++) {
		enfiler_point_ecran(traj_ecran, pt_vide);
	}

}

/*****************************************************************************/