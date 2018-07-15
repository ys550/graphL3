/*****************************************************/

/*****************************************************/
#ifndef __TRAJECTOIRE_ECRAN__
#define __TRAJECTOIRE_ECRAN__
/*****************************************************/

/*
	 Ce module offre  de construire, d'agir et de renseigner une trajectoire
	 de points �cran obtenus dans notre TP3 lors d'un d�placement continu de la souris.

	 Une trajectoire �cran est impl�ment�e dans une file construite par chainage dynamique.

	 On d�finit d'abord publiquement les trois types n�cessaires � la r�alisation
	 et un nombre minimum de fonctions n�cessaires � chaque structure.

	 En tout dernier vient un type d�di� au regroupement de trajectoires
	 �cran, impl�ment� dans un tableau dynamique dont la taille peut varier.
*/

/* le nombre de trajectoires � saisir dans un groupe */
#define NB_TRAJECTOIRES  6

/*****************************************************/
/*
   D�finition d'un point de l'�cran.
   Caract�ristique importante : leurs coordonn�es sont en pixels
   on les conserve dans deux entiers.
   NOTE: ce type est consid�r� "publique" pour tous. On peut donc
   faire directement acc�s � ses 2 champs dans n'importe quel autre
   module ou fichier-client.
*/
typedef struct {
	// la position-pixel du point
	int pos_x;   // coordonn�e horizontale
	int pos_y;   // coordonn�e verticale
} t_point_ecran;

/*****************************************************/
/*****************************************************/
/* 
   D�finition du noeud fait pour contenir un point �cran dans la file.
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
   D�finition de la file repr�sentant une trajectoire-�cran.
   Pour maintenir l'acc�s FIFO d'une file 
   on va INSERER � la fin et EXTRAIRE du d�but.
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

SORTIE: la structure file aux membres bien initialis�s
*/
t_trajectoire_ecran init_trajectoire_ecran(void);

/*****************************************************/
/* INFORMATRICE
obtenir le nombre de points �cran actuellement dans la trajectoire

PARAMETRE : l'adresse de la trajectoire

SORTIE: le nombre d'elements dans la file

SPECS: ne modifie pas la trajectoire
*/
int taille_trajectoire_ecran(const t_trajectoire_ecran * traj);

/*****************************************************/
/* INFORMATRICE
savoir si la trajectoire est vide

PARAMETRE : l'adresse de la trajectoire

SORTIE: 1 si la file est vide, 0 sinon

SPECS: ne modifie pas la trajectoire
*/
int trajectoire_ecran_vide(const t_trajectoire_ecran * traj);

/*****************************************************/
/* MUTATRICE
mettre le pointeur-it�rateur (position courant) au d�but de la file.

PARAMETRE : l'adresse de la trajectoire

SORTIE: aucune
*/
void set_iter_debut(t_trajectoire_ecran * traj);

/*****************************************************/
/* INFORMATRICES
obtenir le point �cran du pointeur-it�rateur et avancer ce pointeur au prochain noeud.
sert dans dessiner la trajectoire

PARAMETRE : l'adresse de la trajectoire

SORTIE: un t_point_ecran

SPECS: si le pointeur-it�rateur est NULL, retour d'un point �cran � coordonn�es
	    pixels non-valides (-1,-1)
*/
t_point_ecran get_point_iter(t_trajectoire_ecran * traj);

/*****************************************************/
/* MUTATRICE
ajoute un noeud contenant un point_ecran � la fin de la trajectoire (FIFO)

PARAMETRES : l'adresse de la trajectoire, l'adresse du point_ecran � ajouter

SORTIE: 1 si l'ajout du noeud est fait, 0 sinon
*/
int enfiler_point_ecran(t_trajectoire_ecran * traj, const t_point_ecran pt);

/*****************************************************/
/* MUTATRICE
�limine le premier noeud de la trajectoire et copie le point �cran dans la r�f�rence (FIFO)

PARAMETRES : l'adresse de la trajectoire, la r�f�rence pr�te � recevoir le t_point_ecran extrait

SORTIE: 0 si la trajectoire �tait vide et 1 sinon.
*/
int defiler_point_ecran(t_trajectoire_ecran * traj,  t_point_ecran * pt);

/*****************************************************/
/* INTERFACE �CRAN
 construire une nouvelle trajectoire obtenue du mouvement continu de la souris
 utiliser mode_graphique.h pour le r�aliser

PARAMETRE : la r�f�rence pr�te � recevoir la nouvelle trajectoire

SORTIE: si la trajectoire est valide, le nombre de points saisis et 0 sinon.
*/
int lire_trajectoire_ecran(t_trajectoire_ecran * traj);     

/*****************************************************/
/* INTERFACE �CRAN
dessiner une  trajectoire dans l'�cran graphique
utiliser mode_graphique.h pour le r�aliser

PARAMETRES : l'adresse de la trajectoire, la couleur d'affichage d�sir�e

SORTIE: Rien
*/
void dessiner_trajectoire_ecran(t_trajectoire_ecran * traj, int couleur);    

/*****************************************************/
/* DESTRUCTEUR supprime tous les noeuds de la trajectoire

PARAMETRE: l'adresse de la trajectoire,

SORTIE: le nombre de noeuds supprim�s

SPECS: tous les noeuds de la trajectoire sont supprim�s, 
	   les trois membres sont remis � 0 ( ou NULL) 
       cette trajectoire pourra �tre reutilis�e 
*/
int liberer_trajectoire_ecran(t_trajectoire_ecran * traj);


/*****************************************************/
/*****************************************************/
// REGROUPER des trajectoires �cran dans un ensemble
// Voici la d�finition d'un groupe de trajectoires �cran

typedef struct {
	// le nombre actuel de trajectoires dans le groupe
	int nb_trajectoire;

	// le tableau dynamique des trajectoires
	t_trajectoire_ecran * tableau_traj;

	// la taille du tableau pr�c�dent, capacit� maximale de trajectoires
	int taille_tableau;
} t_groupe_traj_ecran;


/*****************************************************/
/*****************************************************/
/* CONSTRUCTEUR
Creer un groupe initialement vide mais capable de conserver
un nombre de trajectoires donn� en parametre.

PARAMETRE : la taille du tableau dynamique voulu

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

// Si la position re�ue est correcte, une copie de la trajectoire
// � cette position est retourn�e,
// sinon retour d'une trajectoire vide (tous ses membres = 0).
// La premi�re trajectoire est � la position 0
t_trajectoire_ecran  consulter_groupe(const t_groupe_traj_ecran * groupe, int position);

/*****************************************************/
/* MUTATRICE
Si une place est disponible dans le tableau de ce groupe, 
on ajoute la trajectoire.

PARAMETRES: l'adresse du groupe, l'adresse de la trajectoire � ajouter
    
SORTIE: de 0 ou 1
*/
int ajouter_traj_groupe(t_groupe_traj_ecran * groupe, t_trajectoire_ecran * traj);

/*****************************************************/
/* DESTRUCTEUR 
Supprime toutes les trajectoires du groupe.

PARAMETRE: l'adresse du groupe

SORTIE: le nombre de trajectoires supprim�es

SPECS: tous les noeuds des trajectoires sont supprim�s 
*/
int vider_traj_groupe(t_trajectoire_ecran * traj);

#endif   //!__TRAJECTOIRE_ECRAN__
/**********************************************************/

