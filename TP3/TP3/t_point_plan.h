
typedef struct {
	// la position-pixel du point
	double x;   // coordonnée horizontale
	double y;   // coordonnée verticale
} t_point_plan;


/*
CREER_MATRICE_PTS
Codée par

Cette fonction

PARAMÈTRES :
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
Codée par

Cette fonction

PARAMÈTRES :
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
Codée par

Cette fonction

PARAMÈTRES :
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
Codée par

Cette fonction

PARAMÈTRES :
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
Codée par

Cette fonction

PARAMÈTRES :
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
Codée par

Cette fonction

PARAMÈTRES :
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
Codée par

Cette fonction

PARAMÈTRES :
-tab : (type : t_point_plan *)
-taille :  (type : int)

HYPOTHESES: Aucune.

VALEUR DE RETOUR:  (type : t_point_plan).

EXEMPLES D'APPEL :
-
-
*/
static t_point_plan ecart_type(t_point_plan * tab, int taille);
