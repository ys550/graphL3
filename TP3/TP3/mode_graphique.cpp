/*******************************************************************************
  MODE_GRAPHIQUE.CPP             (INF145: TP3, �T� 2018, Auteur: E.Th�)
	Module d'affichage pour les obstacles. 
	Nec�ssite l'ajout de la librairie "winBGIm.h".
*******************************************************************************/
#include"mode_graphique.h"
#include"winBGIm.h"
#include<math.h>

/*******************************************************************************
                            CONSTANTES PRIV�ES
*******************************************************************************/
//marge pour l'affichage de texte
#define MARGE       50   

//rayon pour un gros point
#define RAYON_PT     5


/*******************************************************************************
                            FONCTIONS PUBLIQUES
*******************************************************************************/

/******************************************************************************
// initialiser_graphique
// ****************************************************************************
// Cette fonction permet d'ouvrir le mode graphique.
******************************************************************************/
void initialiser_graphique()
{	/* request auto detection */
	int gdriver = DETECT, gmode;

	/* initializer graphics mode */
	initgraph(&gdriver, &gmode, "");
}

/******************************************************************************
// fermer_graphique
// ****************************************************************************
// Cette fonction permet de fermer le mode graphique.
// Encapsulation de la fonction � closegraph() � du module � winBGIm.h �.
******************************************************************************/
void  fermer_graphique()
{ closegraph(); }

/*******************************************************************************
// effacer_ecran
// *****************************************************************************
// Cette fonction permet d'effacer la fenetre graphique.
// Encapsulation de la fonction � clearviewport() � du module � winBGIm.h �.
*******************************************************************************/
void  effacer_ecran()
{ clearviewport(); }


/*******************************************************************************
// pause_ecran
// *****************************************************************************
// Cette fonction permet d'effectuer une pause-�cran en mode graphique.
// Encapsulation de la fonction � getch_graph() � du module � winBGIm.h �.
*******************************************************************************/
void  pause_ecran()
{ //l'utilisateur doit appuyer une touche pour terminer la pause-�cran
  getch_graph();
}


/*******************************************************************************
// delai_ecran
// *****************************************************************************
// Cette fonction permet d'effectuer un d�lai de temps en mode graphique.
// Encapsulation de la fonction � delay_graph() � du module � winBGIm.h �.
// PARAMETRES (1) : 
//	     - le temps de d�lai d�sir� en millisecondes (entiers)
*******************************************************************************/
void  delai_ecran(int msec)
{ delay_graph(msec); }


/*******************************************************************************
// afficher_pixel
// *****************************************************************************
// Cette fonction permet d'afficher un pixel d'une couleur sp�cifi�e.
// Encapsulation de la fonction � putpixel() � du module � winBGIm.h �.
// PARAMETRES (3) : 
//	     - pos. du pixel en x et en y (2 entiers)
//       - couleur du pixel (entier)
*******************************************************************************/
void  afficher_pixel(int px, int py, int coul)
{ putpixel(px, py, coul); }


/*******************************************************************************
// obtenir_pixel
// *****************************************************************************
// Cette fonction permet d'obtenir la couleur du pixel � une position donn�e.
// Encapsulation de la fonction � getpixel() � du module � winBGIm.h �.
// PARAMETRES (2) : 
//	     - pos. du pixel en x et en y (2 entiers)
// RETOUR :
//       - la couleur du pixel (entier)
*******************************************************************************/
int  obtenir_pixel(int px, int py)
{ return getpixel(px, py); }


/*******************************************************************************
// afficher_texte
// *****************************************************************************
// Cette fonction permet d'afficher du texte au bas de l'�cran.
// PARAMETRES (1) : 
//       - contenu du texte (string)
*******************************************************************************/
void  afficher_texte(char *text)
{ int px = MARGE,					//position en x
      py = getmaxy() - MARGE;		//position en y au bas de la page

  //premi�rement effacer toute la r�gion d'affichage
  setfillstyle(SOLID_FILL, BLACK);
  bar(px-1, py-1, getmaxx(), getmaxy());

  //en blanc avec police et sens par d�faut, 2 fois la taille normale
  setcolor(WHITE);
  settextstyle(0, 0, 2);
  outtextxy(px, py, text);
}


/*******************************************************************************
// dessiner_pt
// *****************************************************************************
// Cette fonction permet de dessiner un gros point d'une couleur sp�cifi�e.
// PARAMETRES (3) : 
//	     - pos. du point en x et en y (2 entiers)
//       - couleur du point (entier)
*******************************************************************************/
void  dessiner_pt(int px, int py, int coul)
{ //�tablir la couleur d�sir�e
  setcolor(coul);
  circle(px, py, RAYON_PT);    //le contour

  //remplir l'int�rieur
  setfillstyle(SOLID_FILL, coul);
  floodfill(px, py, coul);
}


/*******************************************************************************
// dessiner_cercle
// *****************************************************************************
// Cette fonction permet de dessiner un cercle plein (de couleur OBSTACLE).
// PARAMETRES (3) : 
//	     - pos. du centre en x et en y (2 entiers)
//       - rayon du cercle (entier)
*******************************************************************************/
void  dessiner_cercle(int px, int py, int rayon)
{ //�tablir la couleur d�sir�e
  setcolor(OBSTACLE);
  circle(px, py, rayon);    //le contour

  //remplir l'int�rieur
  setfillstyle(SOLID_FILL, OBSTACLE);
  floodfill(px, py, OBSTACLE);
}


/*******************************************************************************
// dessiner_ellipse
// *****************************************************************************
// Cette fonction permet de dessiner un �llipse plein (de couleur OBSTACLE).
// PARAMETRES (4) : 
//	     - pos. du centre en x et en y (2 entiers)
//       - rayon en X de l'�llipse (entier)
//       - rayon en Y de l'�llipse (entier)
*******************************************************************************/
void  dessiner_ellipse(int px, int py, int rayonx, int rayony)
{ //�tablir la couleur d�sir�e
  setcolor(OBSTACLE);
  ellipse(px, py, 0, 360, rayonx, rayony);    //le contour

  //remplir l'int�rieur
  setfillstyle(SOLID_FILL, OBSTACLE);
  floodfill(px, py, OBSTACLE);
}



/*******************************************************************************
// dessiner_ligne
// *****************************************************************************
// Cette fonction permet de dessiner une grosse ligne d'une couleur sp�cifi�e.
// PARAMETRES (4) : 
//	     - pos. du centre en x et en y (2 entiers)
//       - rayon1 de l'�lipse (entier)
//	     - pos. du premier point en x et en y (2 entiers)
//	     - pos. du deuxi�me point en x et en y (2 entiers)
*******************************************************************************/
void  dessiner_ligne(int x1, int y1, int x2, int y2)
{ //ligne pleine � double-�paisseur
  setcolor(LIMITE);
  setlinestyle(SOLID_LINE, 1, 2);

  line(x1, y1, x2, y2);
}


/*******************************************************************************
// dessiner_rect
// *****************************************************************************
// Cette fonction permet de dessiner un rectangle plein (de couleur OBSTACLE).
// PARAMETRES (4) : 
//	     - pos. du coin sup. gauche en x et en y (2 entiers)
//       - pos. du coin inf. droite en x et en y (2 entiers)
*******************************************************************************/
void  dessiner_rect(int x1, int y1, int x2, int y2)
{ //�tablir couleur de l'int�rieur
  setfillstyle(SOLID_FILL, OBSTACLE);
  bar(x1, y1, x2, y2);
}



/*******************************************************************************
// dessiner_tri
// *****************************************************************************
// Cette fonction permet de dessiner un triangle plein (de couleur OBSTACLE).
// PARAMETRES (6) : 
//	     - pos. du point 1 en x et en y (2 entiers)
//	     - pos. du point 2 en x et en y (2 entiers)
//	     - pos. du point 3 en x et en y (2 entiers)
*******************************************************************************/
void  dessiner_tri(int x1, int y1, int x2, int y2, int x3, int y3)
{ int tab_pts[6] = {x1, y1, x2, y2, x3, y3};    //les 6 coordonn�es des 3 pts.

  //�tablir la couleur d�sir�e
  setcolor(OBSTACLE);

  //�tablir couleur de l'int�rieur
  setfillstyle(SOLID_FILL, OBSTACLE);
  fillpoly(3, tab_pts);
}