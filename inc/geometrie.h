#ifndef COORD_H_
#define COORD_H_

typedef struct {
  int x;
  int y;
} Coord; /* Coordonnée sur ℤ */

typedef struct {
  double x;
  double y;
} Coord_R; /* Coordonnée sur ℝ */

typedef struct {
  int min;
  int max;
} Axe;

typedef struct {
  double min;
  double max;
  double pas; /* Incrément de l'axe */
} Axe_R;

typedef struct Plan_Z_s *Plan_Z;
struct Plan_Z_s{
  Axe abs; /* Axe des Abscisses */
  Axe ord; /* Axe des Ordonnées */
};

typedef struct Plan_R_s *Plan_R;
struct Plan_R_s{
  Axe_R abs; /* Axe des Abscisses */
  Axe_R ord; /* Axe des Ordonnées */
};

/*-----==========Gestion des Coords==========-----*/
/* Crée une coordonnée entière */
Coord init_coord(int x, int y);
/* Renvoie une coordonnée entière relative par rapport au point [dec] */
Coord coord_relative(Coord absolue, Coord dec);
/* Crée une coordonnée réelle */
Coord_R init_coordr(double x, double y);

/*-----==========Gestion des Axes==========-----*/
/* Crée un axe sur les entiers relatifs */
Axe init_axe(int a, int b);
/* Crée un axe sur les entiers réels */
Axe_R init_axer(double a, double b, double pas);

/*-----==========Gestion des Plans==========-----*/
/* Crée un plan sur les entiers relatifs */
Plan_Z init_planz(Axe abs, Axe ord);
/* Libère l'espace occupé par un Plan_Z */
void liberer_planz(Plan_Z *p);
/* Crée un plan sur les entiers réels */
Plan_R init_planr(Axe_R abs, Axe_R ord);
/* Libère l'espace occupé par un Plan_N */
void liberer_planr(Plan_R *p);

/*-----==========Opérations sur les Axes==========-----*/
/* Longueur d'un axe sur ℤ */
int long_axe(Axe a);
/* Longueur d'un axe sur ℝ */
double long_axer(Axe_R a);
/* Convertie une longueur sur ℝ dans ℤ */
int long_rtoz(double longueur, Axe_R axe_in, Axe axe_out);
/* Convertie une longueur sur ℤ dans ℝ */
double long_ztor(int longueur, Axe axe_in, Axe_R axe_out);

/*-----==========Opérations sur les Coords==========-----*/
/* Converti des coordonnées info (y vers le bas) en math (y vers le haut) */
Coord coord_info_en_math(Coord c, Plan_Z z);
/* Converti des coordonnées math (y vers le haut) en info (y vers le bas) */
Coord_R coord_math_en_info(Coord_R c, Plan_R r);
/* Converti des Coord sur ℤ vers ℝ */
Coord_R coord_ztor(Coord c, Plan_R r, Plan_Z z);
/* Converti des Coord sur ℝ vers ℤ */
Coord coord_rtoz(Coord_R cr, Plan_R r, Plan_Z z);

#endif
