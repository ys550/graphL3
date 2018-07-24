/*****************************************************/

/*****************************************************/
#ifndef __TRAJECTOIRE_ECRAN__
#define __TRAJECTOIRE_ECRAN__
/*****************************************************/

/*
	 Ce module offre  de construire, d'agir et de renseigner une trajectoire
	 de points écran obtenus dans notre TP3 lors d'un déplacement continu de la souris.

	 Une trajectoire écran est implémentée dans une file construite par chainage dynamique.

	 On définit d'abord publiquement les trois types nécessaires à la réalisation
	 et un nombre minimum de fonctions nécessaires à chaque structure.

	 En tout dernier vient un type dédié au regroupement de trajectoires
	 écran, implémenté dans un tableau dynamique dont la taille peut varier.

	 Les fonctions définent dans ce module sont :

	 - t_trajectoire_ecran init_trajectoire_ecran(void);
	   (construire une trajectoire vide)

	- int taille_trajectoire_ecran(const t_trajectoire_ecran * traj);
	  ( obtenir le nombre de points écran actuellement dans la trajectoire )
 ) 

	- int trajectoire_ecran_vide(const t_trajectoire_ecran * traj);
	  ( savoir si la trajectoire est vide )

	- void set_iter_debut(t_trajectoire_ecran * traj);
	  ( mettre le pointeur-itérateur (position courant) au début de la file )

	- t_point_ecran get_point_iter(t_trajectoire_ecran * traj);
	  ( obtenir le point écran du pointeur-itérateur et avancer ce pointeur 
	  au prochain noeud et sert dans dessiner la trajectoire )

	- int enfiler_point_ecran(t_trajectoire_ecran * traj, const t_point_ecran pt);
	  ( ajoute un noeud contenant un point_ecran à la fin de la trajectoire )

	- int lire_trajectoire_ecran(t_trajectoire_ecran * traj);  
	 ( construire une nouvelle trajectoire obtenue du mouvement continu de 
	   la souris utiliser mode_graphique.h pour le réaliser )
    
	- void dessiner_trajectoire_ecran(t_trajectoire_ecran * traj, int couleur);  
	  ( dessiner une  trajectoire dans l'écran graphique utiliser 
	    mode_graphique.h pour le réaliser )

	- int liberer_trajectoire_ecran(t_trajectoire_ecran * traj);
	  ( supprime tous les noeuds de la trajectoire ) 

	- t_groupe_traj_ecran init_groupe(int taille);
	  ( Creer un groupe initialement vide mais capable de conserver
        un nombre de trajectoires donné en parametre ) 
  
     - int get_nombre_traj_groupe(const t_groupe_traj_ecran * groupe);
       ( Retourne le nombre actuel de trajectoires  dans le groupe )
	
	 - int get_taille_groupe(const t_groupe_traj_ecran * groupe);
	   ( Retourne la taille actuelle du tableau dynamique du groupe )

	  - t_trajectoire_ecran  consulter_groupe(const t_groupe_traj_ecran
	     * groupe, int position);
		 (Si la position reçue est correcte, une copie de la trajectoire
           à cette position est retournée)

	  - int ajouter_traj_groupe(t_groupe_traj_ecran * groupe, 
	     t_trajectoire_ecran * traj);
		 ( Si une place est disponible dans le tableau de ce groupe, 
           on ajoute la trajectoire )

	 - int vider_traj_groupe(t_groupe_traj_ecran * groupe);
	   ( Supprime toutes les trajectoires du groupe )
*/

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/


/* le nombre de trajectoires à saisir dans un groupe */
#define NB_TRAJECTOIRES  6


/*=========================================================*/
/*                       STRUCTURE                         */
/*=========================================================*/

typedef struct {
	// la position-pixel du point
	int pos_x;   // coordonnée horizontale
	int pos_y;   // coordonnée verticale
} t_point_ecran;

/*****************************************************/
/*****************************************************/
/* 
   Définition du noeud fait pour contenir un point écran dans la file.
   C'est ce noeud qui sert d'atome de la file.
*/
typedef struct noeud * t_lien;

typedef struct noeud {
	t_point_ecran point;
	t_lien suivant;
} t_noeud_ecran;

/*****************************************************/
/*****************************************************/
/* 
   Définition de la file représentant une trajectoire-écran.
   Pour maintenir l'accès FIFO d'une file 
   on va INSERER à la fin et EXTRAIRE du début.
*/

typedef struct {
	int nb_points;
	t_lien tete;
	t_lien queue;
	t_lien ptr_iter; 
} t_trajectoire_ecran;


/*****************************************************/
/*              FONCTIONS PUBLIQUES                  */
/*****************************************************/
/* CONSTRUCTEUR
construire une trajectoire vide

PARAMETRES: aucun

SORTIE: la structure file aux membres bien initialisés
*/
t_trajectoire_ecran init_trajectoire_ecran(void);

/*****************************************************/
/* INFORMATRICE
obtenir le nombre de points écran actuellement dans la trajectoire

PARAMETRE : * traj : l'adresse de la trajectoire

SORTIE: le nombre d'elements dans la file

SPECS: ne modifie pas la trajectoire
*/
int taille_trajectoire_ecran(const t_trajectoire_ecran * traj);

/*****************************************************/
/* INFORMATRICE
savoir si la trajectoire est vide

PARAMETRE : * traj : l'adresse de la trajectoire

SORTIE: 1 si la file est vide, 0 sinon

SPECS: ne modifie pas la trajectoire
*/
int trajectoire_ecran_vide(const t_trajectoire_ecran * traj);

/*****************************************************/
/* MUTATRICE
mettre le pointeur-itérateur (position courant) au début de la file.

PARAMETRE : * traj : l'adresse de la trajectoire

SORTIE: aucune
*/
void set_iter_debut(t_trajectoire_ecran * traj);

/*****************************************************/
/* INFORMATRICES
obtenir le point écran du pointeur-itérateur et avancer ce pointeur au prochain noeud.
sert dans dessiner la trajectoire

PARAMETRE : * traj : l'adresse de la trajectoire

SORTIE: un t_point_ecran

SPECS: si le pointeur-itérateur est NULL, retour d'un point écran à coordonnées
	    pixels non-valides (-1,-1)
*/
t_point_ecran get_point_iter(t_trajectoire_ecran * traj);

/*****************************************************/
/* MUTATRICE
ajoute un noeud contenant un point_ecran à la fin de la trajectoire (FIFO)

PARAMETRES :- * traj : l'adresse de la trajectoire
	        - pt : l'adresse du point_ecran à ajouter

SORTIE: 1 si l'ajout du noeud est fait, 0 sinon
*/
int enfiler_point_ecran(t_trajectoire_ecran * traj, const t_point_ecran pt);

/*****************************************************/
/* MUTATRICE
élimine le premier noeud de la trajectoire et copie le point écran dans la référence (FIFO)

PARAMETRES :- * traj : l'adresse de la trajectoire
			- * pt : la référence prête à recevoir le t_point_ecran extrait

SORTIE: 0 si la trajectoire était vide et 1 sinon.
*/
int defiler_point_ecran(t_trajectoire_ecran * traj,  t_point_ecran * pt);

/*****************************************************/
/* INTERFACE ÉCRAN
 construire une nouvelle trajectoire obtenue du mouvement continu de la souris
 utiliser mode_graphique.h pour le réaliser

PARAMETRE : * traj : la référence prête à recevoir la nouvelle trajectoire

SORTIE: si la trajectoire est valide, le nombre de points saisis et 0 sinon.
*/
int lire_trajectoire_ecran(t_trajectoire_ecran * traj);     

/*****************************************************/
/* INTERFACE ÉCRAN
dessiner une  trajectoire dans l'écran graphique
utiliser mode_graphique.h pour le réaliser

PARAMETRES :- * traj : l'adresse de la trajectoire
            - couleur : la couleur d'affichage désirée

SORTIE: Rien
*/
void dessiner_trajectoire_ecran(t_trajectoire_ecran * traj, int couleur);    

/*****************************************************/
/* DESTRUCTEUR supprime tous les noeuds de la trajectoire

PARAMETRE: * traj : l'adresse de la trajectoire,

SORTIE: le nombre de noeuds supprimés

SPECS: tous les noeuds de la trajectoire sont supprimés, 
	   les trois membres sont remis à 0 ( ou NULL) 
       cette trajectoire pourra être reutilisée 
*/
int liberer_trajectoire_ecran(t_trajectoire_ecran * traj);


/*****************************************************/
/*****************************************************/
// REGROUPER des trajectoires écran dans un ensemble
// Voici la définition d'un groupe de trajectoires écran

typedef struct {
	// le nombre actuel de trajectoires dans le groupe
	int nb_trajectoire;

	// le tableau dynamique des trajectoires
	t_trajectoire_ecran * tableau_traj;

	// la taille du tableau précédent, capacité maximale de trajectoires
	int taille_tableau;
} t_groupe_traj_ecran;


/*****************************************************/
/*****************************************************/
/* CONSTRUCTEUR
Creer un groupe initialement vide mais capable de conserver
un nombre de trajectoires donné en parametre.

PARAMETRE : taille : la taille du tableau dynamique voulu

SORTIE: le nouveau groupe de trajectoires 
*/
t_groupe_traj_ecran init_groupe(int taille);

/*****************************************************/
/*****************************************************/
// TROIS FONCTIONS INFORMATRICES

// Retourne le nombre actuel de trajectoires  dans le groupe
int get_nombre_traj_groupe(const t_groupe_traj_ecran * groupe);

// Retourne la taille actuelle du tableau dynamique du groupe 
int get_taille_groupe(const t_groupe_traj_ecran * groupe);

// Si la position reçue est correcte, une copie de la trajectoire
// à cette position est retournée,
// sinon retour d'une trajectoire vide (tous ses membres = 0).
// La première trajectoire est à la position 0
t_trajectoire_ecran  consulter_groupe(const t_groupe_traj_ecran * groupe, int position);

/*****************************************************/
/* MUTATRICE
Si une place est disponible dans le tableau de ce groupe, 
on ajoute la trajectoire.

PARAMETRES:- * groupe : l'adresse du groupe
		   - *traj : l'adresse de la trajectoire à ajouter
    
SORTIE: de 0 ou 1
*/
int ajouter_traj_groupe(t_groupe_traj_ecran * groupe, t_trajectoire_ecran * traj);

/*****************************************************/
/* DESTRUCTEUR 
Supprime toutes les trajectoires du groupe.

PARAMETRE: * groupe : l'adresse du groupe

SORTIE: le nombre de trajectoires supprimées

SPECS: tous les noeuds des trajectoires sont supprimés 
*/
int vider_traj_groupe(t_groupe_traj_ecran * groupe);

#endif   //!__TRAJECTOIRE_ECRAN__
/**********************************************************/

