#ifndef GRILLE_H_
#define GRILLE_H_

#include <stdbool.h>
#include "geometrie.h"
#include "position.h"

typedef struct {
  int x;
  int y;
  int cote;
} Grid;

Grid init_grille(int x, int y, int dimension, bool est_x);
int grille_longueur(Grid grille);
int grille_hauteur(Grid grille);
int grille_dist(int dist, Grid grille);
Coord grille_coord(int x, int y, Grid grille);
MLV_Position grille_pos(int dec_x, int dec_y, int dim_x, int dim_y, Grid g);

#endif
