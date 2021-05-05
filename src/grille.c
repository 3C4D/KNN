#include "grille.h"

/*-----==========Gestion de la Grille==========-----*/
/* Crée une grille à partir d'une dimension donnée qui est soit en x ou en y*/
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

/* Renvoie la longueur de la grille */
int grille_longueur(Grid grille){
  return (grille.x * grille.cote);
}

/* Renvoie la hauteur de la grille */
int grille_hauteur(Grid grille){
  return (grille.y * grille.cote);
}

/* Converti une longueur sur la grille en longueur sur la fenêtre */
int grille_dist(int dist, Grid grille){
  return (dist * grille.cote);
}

/* Converti une coordonnée sur la grille en coordonnée sur la fenêtre */
Coord grille_coord(int x, int y, Grid grille){
  return (init_coord(grille_dist(x, grille), grille_dist(y, grille)));
}

/* Converti une position sur la grille en position sur la fenêtre */
MLV_Position grille_pos(int dec_x, int dec_y, int dim_x, int dim_y, Grid g){
  return (
    init_positon(
      grille_coord(dec_x, dec_y, g),
      grille_coord(dim_x, dim_y, g)
    )
  );
}
