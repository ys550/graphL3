/*

Module : TP3_main.cpp
Par    : Youssef Soliman, Hugo Belin
Date   : 2018-07-08
*/

#define _CRT_SECURE_NO_WARNINGS

// Librairies usuelles � inclure 
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>     //pour: kbhit() et _getch()

// Librairies pour les fonctions definis dans le projet
#include"winBGIm.h"
#include "mode_graphique.h"
#include "t_obstacles.h"
#include "trajectoire_ecran.h"

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

//Les noms et trajets des fichiers
#define FICHIER_TRAJET_1 "trajet1.txt"
#define FICHIER_TRAJET_2 "trajet2.txt"
#define FICHIER_TRAJET_3 "trajet3.txt"
#define FICHIER_TRAJET_4 "trajet4.txt"
#define FICHIER_TRAJET_INDY "trajet_INDY.txt"

//Pour l'execution des mandats: 1: active 0: desactive
#define MANDAT1 0
#define MANDAT2 1

//Pour le test de correlation
#define TAILLE  4

/********************************************************************/
/*				DECLARATIONS DES FONCTIONS PRIV�ES					*/
/********************************************************************/

static void afficher_menu();
static void choisir_option_menu(t_liste_obs * liste);
static void sequence_affichage_forme(t_liste_obs * liste, char * nom_fich);
static void affichage_traj(t_liste_obs * liste, char * nom_fich);

/*=========================================================*/
/*=========================================================*/
//Programme principal: fonction qui retourne un entier (int)
int main(void) {

	//TEST MANDATS
	#if(1)
		t_liste_obs liste;

		liste.tab_obstacles = NULL;
	
		choisir_option_menu(&liste);
		detruire_obstacles(&liste);
	#endif

	return EXIT_SUCCESS;
}

/*********************************************************/
/*          DEFINITIONS DES FONCTIONS PRIV�ES            */
/*********************************************************/

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

static void choisir_option_menu(t_liste_obs * liste) {
	unsigned char option;
	

	do {
		afficher_menu();

		//Attente touche du clavier
		while (!_kbhit()) {}
		//retourne la touche
		option = _getch();

		switch (option) {
		case '1':
			#if(MANDAT1)
				sequence_affichage_forme(liste, FICHIER_TRAJET_1);
			#endif

			#if(MANDAT2)
				affichage_traj(liste, FICHIER_TRAJET_1);
			#endif
			break;
		case '2':
			#if(MANDAT1)
				sequence_affichage_forme(liste, FICHIER_TRAJET_2);
			#endif

			#if(MANDAT2)
				affichage_traj(liste, FICHIER_TRAJET_2);
			#endif
			break;
		case '3':
			#if(MANDAT1)
				sequence_affichage_forme(liste, FICHIER_TRAJET_3);
			#endif

			#if(MANDAT2)
				affichage_traj(liste, FICHIER_TRAJET_3);
			#endif
			break;
		case '5':
			#if(MANDAT1)
				sequence_affichage_forme(liste, FICHIER_TRAJET_INDY);
			#endif

			#if(MANDAT2)
				affichage_traj(liste, FICHIER_TRAJET_INDY);
			#endif
			break;
		case 'q':
		case 'Q':
			break;
		default:
			#if(MANDAT1)
			sequence_affichage_forme(liste, FICHIER_TRAJET_4);
			#endif

			#if(MANDAT2)
				affichage_traj(liste, FICHIER_TRAJET_4);
			#endif
			break;
		}

	} while (option != 'q' && option != 'Q');

}

/******************************MANDAT 1************************************/
static void sequence_affichage_forme(t_liste_obs * liste, char * nom_fich) {

	int nb_points;
	char nb_point_char[100];

	nb_points = lire_obstacles(nom_fich, liste);

	//conversion nb_point (int) a nb_points(char)
	sprintf(nb_point_char, 
		"taille normalisee = %d pts.\t Appuyer une touche...", nb_points);

	initialiser_graphique();
	dessiner_obstacles(liste);
	afficher_texte(nb_point_char);
	pause_ecran();
	fermer_graphique();
	
}

/*************************MANDAT 2********************************/
static void affichage_traj(t_liste_obs * liste, char * nom_fich) {
	int i;
	int nb_points;
	int nb_points_saisis;
	char nb_points_saisis_char[100];
	char msg_dessiner[200];
	t_trajectoire_ecran traj;
	t_groupe_traj_ecran groupe_traj;

	
	//on initialise un groupe de trajectoires
	groupe_traj = init_groupe(NB_TRAJECTOIRES);

	nb_points = lire_obstacles(nom_fich, liste);
	

	initialiser_graphique();

	//Avec une boucle
	do {
		
		//vous effacez l��cran
		effacer_ecran();
		//dessinez les obstacles du parcours choisi
		dessiner_obstacles(liste);
		//initialisez une variable-trajectoire
		traj = init_trajectoire_ecran();

		sprintf(msg_dessiner, "taille normalisee = %d pts. dessinez le trajet "
			"%d...", nb_points, get_nombre_traj_groupe(&groupe_traj) + 1);
		afficher_texte(msg_dessiner);

		//faites la saisie d�une trajectoire dans le parcours
		//retourne 0 lorsque la trajectoire est non-valide
		nb_points_saisis = lire_trajectoire_ecran(&traj);

		//si la trajectoire est non-valide
		if (nb_points_saisis == 0) {
			//vider cette trajectoire-�cran
			liberer_trajectoire_ecran(&traj);
		}
		//si non
		else {
			//ajouter la trajectoire valide au groupe de trajectoire
			ajouter_traj_groupe(&groupe_traj, &traj);
			sprintf(nb_points_saisis_char, "Fin de saisie de %d pts.\t Appuyez"
				" une touche..", nb_points_saisis);
			afficher_texte(nb_points_saisis_char);
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
	fermer_graphique();

}