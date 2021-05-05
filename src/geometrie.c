#include <stdlib.h>
#include <math.h>
#include "geometrie.h"
#include "erreur.h"

/*-----==========Gestion des Coords==========-----*/
/* Crée une coordonnée entière */
Coord init_coord(int x, int y){
  Coord c;
  c.x = x;
  c.y = y;

  return c;
}

/* Renvoie une coordonnée entière relative par rapport au point [dec] */
Coord coord_relative(Coord absolue, Coord dec){
  return (init_coord(absolue.x - dec.x, absolue.y - dec.y));
}

/* Crée une coordonnée réelle */
Coord_R init_coordr(double x, double y){
  Coord_R c;
  c.x = x;
  c.y = y;

  return c;
}

/*-----==========Gestion des Axes==========-----*/
/* Crée un axe sur les entiers relatifs */
Axe init_axe(int a, int b){
  Axe axe;
  if (a < b) {
    axe.min = a;
    axe.max = b;
  } else {
    axe.min = b;
    axe.max = a;
  }

  return axe;
}

/* Crée un axe sur les entiers réels */
Axe_R init_axer(double a, double b, double pas){
  Axe_R axe;
  if (a < b) {
    axe.min = a;
    axe.max = b;
  } else {
    axe.min = b;
    axe.max = a;
  }
  
  axe.pas = pas;

  return axe;
}

/*-----==========Gestion des Plans==========-----*/
/* Crée un plan sur les entiers relatifs */
Plan_Z init_planz(Axe abs, Axe ord){
  Plan_Z p = malloc(sizeof(struct Plan_Z_s));
  verif_alloc(p);
  p->abs = abs;
  p->ord = ord;

  return p;
}

/* Libère l'espace occupé par un Plan_Z */
void liberer_planz(Plan_Z *p){
  if (*p != NULL){
    free(*p);
  }
  
  *p = NULL;
}

/* Crée un plan sur les entiers réels */
Plan_R init_planr(Axe_R abs, Axe_R ord){
  Plan_R p = malloc(sizeof(struct Plan_R_s));
  verif_alloc(p);
  p->abs = abs;
  p->ord = ord;

  return p;
}

/* Libère l'espace occupé par un Plan_N */
void liberer_planr(Plan_R *p){
  if (*p != NULL){
    free(*p);
  }
  
  *p = NULL;
}

/*-----==========Opérations sur les Axes==========-----*/
/* Longueur d'un axe sur ℤ */
int long_axe(Axe a){
  return(abs(a.max - a.min));
}

/* Longueur d'un axe sur ℝ */
double long_axer(Axe_R a){
  return(fabs(a.max - a.min));
}

/* Convertie une longueur sur ℝ dans ℤ */
int long_rtoz(double longueur, Axe_R axe_in, Axe axe_out){
  return ((int)round((longueur / long_axer(axe_in)) * long_axe(axe_out)));
}

/* Convertie une longueur sur ℤ dans ℝ */
double long_ztor(int longueur, Axe axe_in, Axe_R axe_out){
  return ((longueur / (double)long_axe(axe_in)) * long_axer(axe_out));
}

/*-----==========Opérations sur les Coords==========-----*/
/* Converti des coordonnées info (y vers le bas) en math (y vers le haut) */
Coord coord_info_en_math(Coord c, Plan_Z z){
  Coord out;

  int y = (int)round(
    z->ord.min + 
    (1.0 - (c.y - z->ord.min) / (double)long_axe(z->ord)) * long_axe(z->ord)
  );
  out = init_coord(c.x, y);
  return(out);
}

/* Converti des coordonnées math (y vers le haut) en info (y vers le bas) */
Coord_R coord_math_en_info(Coord_R c, Plan_R r){
  Coord_R out;

  double y = (
    r->ord.min + 
    (1.0 - (c.y - r->ord.min) / long_axer(r->ord)) * long_axer(r->ord)
  );
  out = init_coordr(c.x, y);
  return(out);
}

/* Converti des Coord sur ℝ vers ℤ */
Coord coord_rtoz(Coord_R cr, Plan_R r, Plan_Z z){
  Coord c;
  cr = coord_math_en_info(cr, r);
  int x = z->abs.min + long_rtoz(cr.x - r->abs.min, r->abs, z->abs);
  int y = z->ord.min + long_rtoz(cr.y - r->ord.min, r->ord, z->ord);
  c = init_coord(x, y);

  return c;
}

/* Converti des Coord sur ℤ vers ℝ */
Coord_R coord_ztor(Coord c, Plan_R r, Plan_Z z){
  Coord_R cr;
  c = coord_info_en_math(c, z);
  double x = r->abs.min + long_ztor(c.x - z->abs.min, z->abs, r->abs);
  double y = r->ord.min + long_ztor(c.y - z->ord.min, z->ord, r->ord);
  cr = init_coordr(x, y);

  return cr;
}
