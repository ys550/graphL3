/********************************************************************/
/* Par       : Eric Th�       								        */
/* Fichier   : SOURISLIB.H 									       	*/
/*															   		*/
/* Ce module implante des fonctions de gestion de souris de base.   */
/* Utilise des commandes de la librairie standard <winuser.h>.		*/
/********************************************************************/
#include "winbgim.h"  //contient les fonctions de souris

/* Toutes les positions-�crans utilis�es ici sont absolues, donc on */
/* ne tiens pas compte de l'existence d'un "viewport" d'affichage : */
/*    * = avec (0, 0) au coin sup. gauche de l'�cran  */

/* Permet de positionner la souris a la position-�cran* (x, y). */
void  positionneSouris(int x, int y);

/* Permet d'obtenir la position absolue* actuelle (x, y) de la souris. */
void  obtientSouris(int *x, int *y);

/* Permet d'obtenir la coordonn�e absolue* "x" de la position actuelle */ 
int  sourisX(void);

/* Permet d'obtenir la coordonn�e absolue* "y" de la position actuelle */
int  sourisY(void);

/* Permet de savoir si le bouton de gauche de la souris � �t� pes� */
int  boutonPese(void);

/* Permet de savoir si le bouton de gauche de la souris � �t� relach� */
int  boutonReleve(void);

/* Permet de savoir si le bouton de gauche de la souris � �t� relach� */
int  sourisBouge(void);

/* Cette fonction va attendre que le bouton gauche soit pes� */
void attendBoutonPese(void);

/* Cette fonction va attendre que le bouton gauche soit relev� */
void attendBoutonReleve(void);

/* Fonction qui test si la position actuelle de la souris est dans 
   les limites donn�es par (x1, y1) (x2, y2) */
int testRegionSouris(int x1, int y1, int x2, int y2);

//-------------------------------------------------------------------
//-------------------------------------------------------------------












