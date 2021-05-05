/*
Ce module permet la division de la fenếtre en une grille orthonormée afin de 
placer les éléments de manière relative à celle-ci et non la dimension de 
la fenếtre directment
*/

#ifndef GRILLE_H_
#define GRILLE_H_

#include <stdbool.h>
#include "geometrie.h"
#include "position.h"

typedef struct {
  int x; /* Nombre de case sur l'axe des x */
  int y; /* Nombre de case sur l'axe des y */
  int cote; /* Dimension du coté d'une case */
} Grid;

/*-----==========Gestion de la Grille==========-----*/
/* Crée une grille à partir d'une dimension donnée qui est soit en x ou en y*/
Grid init_grille(int x, int y, int dimension, bool est_x);
/* Renvoie la longueur de la grille */
int grille_longueur(Grid grille);
/* Renvoie la hauteur de la grille */
int grille_hauteur(Grid grille);
/* Converti une longueur sur la grille en longueur sur la fenêtre */
int grille_dist(int dist, Grid grille);
/* Converti une coordonnée sur la grille en coordonnée sur la fenêtre */
Coord grille_coord(int x, int y, Grid grille);
/* Converti une position sur la grille en position sur la fenêtre */
MLV_Position grille_pos(int dec_x, int dec_y, int dim_x, int dim_y, Grid g);

#endif
