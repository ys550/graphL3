
typedef struct {
	// la position-pixel du point
	double x;   // coordonnée horizontale
	double y;   // coordonnée verticale
} t_point_plan;


t_point_plan ** creer_matrice_pts(int taille);
t_point_plan correlation_pts(t_point_plan * tabA, t_point_plan * tabB,
	int taille);
int  trouver_col_min(t_point_plan ** mat_corr, int taille);
void detruire_matrice_pts(t_point_plan ** mat, int taille);

static t_point_plan esperance(t_point_plan * tab, int taille);
static t_point_plan * produit(t_point_plan * tabA, t_point_plan * tabB,
	int taille);
static t_point_plan ecart_type(t_point_plan * tab, int taille);
