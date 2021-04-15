#include <stdlib.h>
#include <math.h>
#include "geometrie.h"
#include "erreur.h"

/* Gestion de la structure Coord */
Coord init_coord(int x, int y){
  Coord c;
  c.x = x;
  c.y = y;

  return c;
}

/* Gestion de la structure Coord_R */
Coord_R init_coordr(double x, double y){
  Coord_R c;
  c.x = x;
  c.y = y;

  return c;
}

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

Plan_Z init_planz(Axe abs, Axe ord){
  Plan_Z p = malloc(sizeof(struct Plan_Z_s));
  verif_alloc(p);
  p->abs = abs;
  p->ord = ord;

  return p;
}

void liberer_planz(Plan_Z *p){
  if (*p != NULL){
    free(*p);
  }
  
  *p = NULL;
}

Plan_R init_planr(Axe_R abs, Axe_R ord){
  Plan_R p = malloc(sizeof(struct Plan_R_s));
  verif_alloc(p);
  p->abs = abs;
  p->ord = ord;

  return p;
}

void liberer_planr(Plan_R *p){
  if (*p != NULL){
    free(*p);
  }
  
  *p = NULL;
}

int long_axe(Axe a){
  return(abs(a.max - a.min));
}

double long_axer(Axe_R a){
  return(fabs(a.max - a.min));
}

int long_rtoz(double longueur, Axe_R axe_in, Axe axe_out){
  return ((int)round((longueur / long_axer(axe_in)) * long_axe(axe_out)));
}

double long_ztor(int longueur, Axe axe_in, Axe_R axe_out){
  return ((longueur / (double)long_axe(axe_in)) * long_axer(axe_out));
}

Coord coord_info_en_math(Coord c, Plan_Z z){
  Coord out;

  int y = (int)round(
    z->ord.min + 
    (1.0 - (c.y - z->ord.min) / (double)long_axe(z->ord)) * long_axe(z->ord)
  );
  out = init_coord(c.x, y);
  return(out);
}

Coord_R coord_math_en_info(Coord_R c, Plan_R r){
  Coord_R out;

  double y = (
    r->ord.min + 
    (1.0 - (c.y - r->ord.min) / long_axer(r->ord)) * long_axer(r->ord)
  );
  out = init_coordr(c.x, y);
  return(out);
}

Coord coord_rtoz(Coord_R cr, Plan_R r, Plan_Z z){
  Coord c;
  cr = coord_math_en_info(cr, r);
  int x = z->abs.min + long_rtoz(cr.x - r->abs.min, r->abs, z->abs);
  int y = z->ord.min + long_rtoz(cr.y - r->ord.min, r->ord, z->ord);
  c = init_coord(x, y);

  return c;
}

Coord_R coord_ztor(Coord c, Plan_R r, Plan_Z z){
  Coord_R cr;
  c = coord_info_en_math(c, z);
  double x = r->abs.min + long_ztor(c.x - z->abs.min, z->abs, r->abs);
  double y = r->ord.min + long_ztor(c.y - z->ord.min, z->ord, r->ord);
  cr = init_coordr(x, y);

  return cr;
}
