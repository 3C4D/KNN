#ifndef POINTS_H_
#define POINTS_H_

/* Structure permettant de représenter un point dans le plan ainsi que sa classe */
typedef struct point{
  double *coord;
  int classe;
}point;

typedef struct TabPts{
  point *tab;
  int taille;
  int dimension;
  int nbclasse;
}TabPts;

/* Permet de créer une structure point en prenant les composantes de cette structure en paramètre */
point creer_point(int dimension, int classe);

/* Ajoute les coordonnées contenues dans un tableau dans un point */
void ajouter_coord(point *pt, int dimension, double *coord);

/* Permet de créer un tableau de points */
TabPts creer_tab_pts(int dimension, int nbclasse);

/* Permet de calculer la distance euclidienne entre deux points */
double calc_distance(point p1, point p2, int dimension);

/* Permet d'ajouter un point au tableau de points */
void ajouter_point(TabPts *tab_pts, point pt);

/* Permet de supprimer un point du tableau de points dont on connait l'index */
void supprimer_point(TabPts *tab_pts, int index);

/* Affiche un point */
void afficher_pt(point pt, int dimension);

/* Affiche un tableau de points */
void afficher_tab_pts(TabPts tab_pts);

/* Retourne la classe la plus présente dans un tableau de points */
int classe_majoritaire(TabPts tab);

#endif
