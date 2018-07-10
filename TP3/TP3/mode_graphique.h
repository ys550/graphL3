/*******************************************************************************
  MODE_GRAPHIQUE.H             (INF145: TP3, �T� 2018, Auteur: E.Th�)
	Module d'affichage pour les obstacles. 
	Nec�ssite l'ajout de la librairie "winBGIm.h".
*******************************************************************************/

#if (!defined(OBSTACLE))

/**************************
  LES CONSTANTES-COULEURS
**************************/

#define  OBSTACLE        BLUE   //un obstacle � contourner (de l'eau)
#define  MOYENNE        WHITE   //couleur de la trajectoire moyenne
#define  DEPART         GREEN   //point de d�part
#define  ARRIVEE      MAGENTA   //point d'arriv�e
#define  NON_VALIDE       RED   //point rejet�
#define  VALIDE        YELLOW   //point accept�
#define  LIMITE		LIGHTGRAY   //mur ou frontiere

/**************************
  LES CONSTANTES-FORMES
/**************************/

#define NB_FORMES  6

//Voici la liste des formes et objets qui peuvent �tre dessin�s par ce module
enum formes {PT, CERCLE, ELLIPSE, LIGNE, RECTANGLE, TRIANGLE};



/**************************
  LES FONCTIONS
/**************************/

/*******************************************************************************
// initialiser_graphique
// *****************************************************************************
// Cette fonction permet d'ouvrir le mode graphique.
*******************************************************************************/
void  initialiser_graphique();


/*******************************************************************************
// fermer_graphique
// *****************************************************************************
// Cette fonction permet de fermer le mode graphique.
*******************************************************************************/
void  fermer_graphique();


/*******************************************************************************
// effacer_ecran
// *****************************************************************************
// Cette fonction permet d'effacer la fenetre graphique.
*******************************************************************************/
void  effacer_ecran();


/*******************************************************************************
// pause_ecran
// *****************************************************************************
// Cette fonction permet d'effectuer une pause-�cran en mode graphique.
*******************************************************************************/
void  pause_ecran();


/*******************************************************************************
// delai_ecran
// *****************************************************************************
// Cette fonction permet d'effectuer un d�lai de temps en mode graphique.
// PARAMETRES (1) : 
//	     - le temps de d�lai d�sir� en millisecondes (entiers)
*******************************************************************************/
void  delai_ecran(int msec);


/*******************************************************************************
// afficher_pixel
// *****************************************************************************
// Cette fonction permet d'afficher un pixel d'une couleur sp�cifi�e.
// PARAMETRES (3) : 
//	     - pos. du pixel en x et en y (2 entiers)
//       - couleur du pixel (entier)
*******************************************************************************/
void  afficher_pixel(int px, int py, int coul);


/*******************************************************************************
// obtenir_pixel
// *****************************************************************************
// Cette fonction permet d'obtenir la couleur du pixel � une position donn�e.
// PARAMETRES (2) : 
//	     - pos. du pixel en x et en y (2 entiers)
// RETOUR :
//       - la couleur du pixel (entier)
*******************************************************************************/
int  obtenir_pixel(int px, int py);


/*******************************************************************************
// afficher_texte
// *****************************************************************************
// Cette fonction permet d'afficher du texte au bas de l'�cran.
// PARAMETRES (1) : 
//       - contenu du texte (string)
*******************************************************************************/
void  afficher_texte(char *text);


/*******************************************************************************
// dessiner_pt
// *****************************************************************************
// Cette fonction permet de dessiner un gros point d'une couleur sp�cifi�e.
// PARAMETRES (3) : 
//	     - pos. du point en x et en y (2 entiers)
//       - couleur du point (entier)
*******************************************************************************/
void  dessiner_pt(int px, int py, int coul);


/*******************************************************************************
// dessiner_cercle
// *****************************************************************************
// Cette fonction permet de dessiner un cercle plein (de couleur OBSTACLE).
// PARAMETRES (3) : 
//	     - pos. du centre en x et en y (2 entiers)
//       - rayon du cercle (entier)
*******************************************************************************/
void  dessiner_cercle(int px, int py, int rayon);


/*******************************************************************************
// dessiner_ellipse
// *****************************************************************************
// Cette fonction permet de dessiner un �llipse plein (de couleur OBSTACLE).
// PARAMETRES (4) : 
//	     - pos. du centre en x et en y (2 entiers)
//       - rayon en X de l'�llipse (entier)
//       - rayon en Y de l'�llipse (entier)
*******************************************************************************/
void  dessiner_ellipse(int px, int py, int rayonx, int rayony);


/*******************************************************************************
// dessiner_ligne
// *****************************************************************************
// Cette fonction permet de dessiner une grosse ligne d'une couleur sp�cifi�e.
// PARAMETRES (4) : 
//	     - pos. du premier point en x et en y (2 entiers)
//	     - pos. du deuxi�me point en x et en y (2 entiers)
*******************************************************************************/
void  dessiner_ligne(int x1, int y1, int x2, int y2);


/*******************************************************************************
// dessiner_rect
// *****************************************************************************
// Cette fonction permet de dessiner un rectangle plein (de couleur OBSTACLE).
// PARAMETRES (4) : 
//	     - pos. du coin sup. gauche en x et en y (2 entiers)
//       - pos. du coin inf. droite en x et en y (2 entiers)
*******************************************************************************/
void  dessiner_rect(int x1, int y1, int x2, int y2);


/*******************************************************************************
// dessiner_tri
// *****************************************************************************
// Cette fonction permet de dessiner un triangle plein (de couleur OBSTACLE).
// PARAMETRES (6) : 
//	     - pos. du point 1 en x et en y (2 entiers)
//	     - pos. du point 2 en x et en y (2 entiers)
//	     - pos. du point 3 en x et en y (2 entiers)
*******************************************************************************/
void  dessiner_tri(int x1, int y1, int x2, int y2, int x3, int y3);

#endif