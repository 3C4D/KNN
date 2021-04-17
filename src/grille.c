#include "grille.h"

Grid init_grille(int x, int y, int dimension, bool est_x){
  Grid grille;
  grille.x = x;
  grille.y = y;

  if (est_x) {
    grille.cote = dimension / x;
  } else {
    grille.cote = dimension / y;
  }

  return grille;
}

int grille_longueur(Grid grille){
  return (grille.x * grille.cote);
}

int grille_hauteur(Grid grille){
  return (grille.y * grille.cote);
}

int grille_dist(int dist, Grid grille){
  return (dist * grille.cote);
}

Coord grille_coord(int x, int y, Grid grille){
  return (init_coord(grille_dist(x, grille), grille_dist(y, grille)));
}

MLV_Position grille_pos(int dec_x, int dec_y, int dim_x, int dim_y, Grid g){
  return (
    init_positon(
      grille_coord(dec_x, dec_y, g),
      grille_coord(dim_x, dim_y, g)
    )
  );
}
