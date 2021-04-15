#ifndef CANVAS_H_
#define CANVAS_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "position.h"
#include "geometrie.h"
#include "texte.h"

struct MLV_Canvas_s{
  MLV_Image *img;
  Coord placement;
  bool visible;
};
typedef struct MLV_Canvas_s *MLV_Canvas;

MLV_Canvas init_canvas(MLV_Position pos, bool visibilite);
MLV_Canvas init_canvas_img(Coord dimension, char *img_rep, bool visibilite);
void liberer_canvas(MLV_Canvas *canvas);
void changer_visibilite(MLV_Canvas canvas);
bool est_visible(MLV_Canvas canvas);
void redimensionner_canvas(Coord dimension, MLV_Canvas canvas);
void couleur_fond_canvas(MLV_Color col, MLV_Canvas canvas);
void placer_texte(char *texte, MLV_Color col, MLV_Canvas canvas);
void placer_ligne(Coord debut, Coord fin, MLV_Color col, MLV_Canvas canvas);
void placer_ellipse_pleine(
  Coord centre, Coord rayon, MLV_Color col, MLV_Canvas cnvs
);
void placer_ellipse(Coord centre, Coord rayon, MLV_Color col, MLV_Canvas cnvs);
void placer_curseur_texte(MLV_Text texte, MLV_Color col, MLV_Canvas canvas);
void afficher_canvas(MLV_Canvas canvas);

#endif
