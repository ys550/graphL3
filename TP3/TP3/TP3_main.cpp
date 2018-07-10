#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>     //pour: kbhit() et _getch()
#include"winBGIm.h"
#include "mode_graphique.h"
#include "t_obstacles.h"

#define FICHIER_TRAJET_1 "trajet1.txt"
#define FICHIER_TRAJET_2 "trajet2.txt"
#define FICHIER_TRAJET_3 "trajet3.txt"
#define FICHIER_TRAJET_4 "trajet4.txt"
#define FICHIER_TRAJET_INDY "trajet_INDY.txt"


static void afficher_menu();
void choisir_option_menu(t_liste_obs * liste);
static void sequence_affichage_forme(t_liste_obs * liste, char * nom_fich);

int main(void) {
	t_liste_obs liste;
	
	#if(0)
		int entier_a_convertir = 1020;
		char entier_en_char[20];

		int2char(entier_en_char, entier_a_convertir);
		puts(entier_en_char);
		system("pause");
	#endif

	//mettre TEST_OBSTACLE a 1
#if(0)
	lire_obstacles(FICHIER_TRAJET_1, &liste);
	initialiser_graphique();
	dessiner_obstacles(&liste);
	pause_ecran();
#endif

#if(0)
	lire_obstacles(FICHIER_TRAJET_2, &liste);
	initialiser_graphique();
	dessiner_obstacles(&liste);
	pause_ecran();
#endif

#if(0)
	lire_obstacles(FICHIER_TRAJET_3, &liste);
	initialiser_graphique();
	dessiner_obstacles(&liste);
	pause_ecran();
#endif

#if(0)
	lire_obstacles(FICHIER_TRAJET_4, &liste);
	initialiser_graphique();
	dessiner_obstacles(&liste);
	pause_ecran();
#endif

#if(0)
	lire_obstacles(FICHIER_TRAJET_INDY, &liste);
	initialiser_graphique();
	dessiner_obstacles(&liste);
	pause_ecran();
#endif

	//Test detruire obstacle
#if(0)
	lire_obstacles(FICHIER_TRAJET_INDY, &liste);
	initialiser_graphique();
	detruire_obstacles(&liste);
	dessiner_obstacles(&liste);
	pause_ecran();
#endif

	//mettre TEST_OBSTACLE a 0
#if(1)
	choisir_option_menu(&liste);
#endif

	return EXIT_SUCCESS;
}

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

void choisir_option_menu(t_liste_obs * liste) {
	unsigned char option;
	

	do {
		afficher_menu();

		//Attente touche du clavier
		while (!_kbhit()) {}
		//retourne la touche
		option = _getch();

		switch (option) {
		case '1':
			sequence_affichage_forme(liste, FICHIER_TRAJET_1);
			break;
		case '2':
			sequence_affichage_forme(liste, FICHIER_TRAJET_2);
			break;
		case '3':
			sequence_affichage_forme(liste, FICHIER_TRAJET_3);
			break;
		case '5':
			sequence_affichage_forme(liste, FICHIER_TRAJET_INDY);
			break;
		case 'q':
		case 'Q':
			break;
		default:
			sequence_affichage_forme(liste, FICHIER_TRAJET_4);
			break;
		}

	} while (option != 'q' && option != 'Q');

}
static void sequence_affichage_forme(t_liste_obs * liste, char * nom_fich) {

	int nb_points;
	char nb_point_char[20];

	nb_points = lire_obstacles(nom_fich, liste);
	int2char(nb_point_char, nb_points);
	initialiser_graphique();
	dessiner_obstacles(liste);
	afficher_texte(nb_point_char);
	pause_ecran();
	fermer_graphique();
	detruire_obstacles(liste);
}