
typedef struct {
	// la position-pixel du point
	double x;   // coordonn�e horizontale
	double y;   // coordonn�e verticale
} t_point_plan;


/*
CREER_MATRICE_PTS
Cod�e par

Cette fonction

PARAM�TRES :
-taille :  (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan **).

EXEMPLES D'APPEL :
-
-
*/
t_point_plan ** creer_matrice_pts(int taille);

/*
CORRELATION_PTS
Cod�e par

Cette fonction

PARAM�TRES :
-tabA : (type : t_point_plan *)
-tabB : (type : t_point_plan *)
-taille :  (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan).

EXEMPLES D'APPEL :
-
-
*/
t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
TROUVER_COL_MIN
Cod�e par

Cette fonction

PARAM�TRES :
-mat_corr : (type : t_point_plan **)
-taille :  (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : int).

EXEMPLES D'APPEL :
-
-
*/
int  trouver_col_min(t_point_plan ** mat_corr, int taille);

/*
DETRUIRE_MATRICE_PTS
Cod�e par

Cette fonction

PARAM�TRES :
-mat : (type : t_point_plan **)
-taille :  (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  rien.

EXEMPLES D'APPEL :
-
-
*/
void detruire_matrice_pts(t_point_plan ** mat, int taille);

/*
ESPERANCE
Cod�e par

Cette fonction

PARAM�TRES :
-tab : (type : t_point_plan *)
-taille :  (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan).

EXEMPLES D'APPEL :
-
-
*/
static t_point_plan esperance(t_point_plan * tab, int taille);

/*
PRODUIT
Cod�e par

Cette fonction

PARAM�TRES :
-tabA : (type : t_point_plan *)
-tabB : (type : t_point_plan *)
-taille :  (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan *).

EXEMPLES D'APPEL :
-
-
*/
static t_point_plan * produit(t_point_plan * tabA, t_point_plan * tabB,
	int taille);

/*
ECRAT_TYPE
Cod�e par

Cette fonction

PARAM�TRES :
-tab : (type : t_point_plan *)
-taille :  (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan).

EXEMPLES D'APPEL :
-
-
*/
static t_point_plan ecart_type(t_point_plan * tab, int taille);
