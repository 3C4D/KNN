/*
Ce module permet la création et l'utilisation de Canvas qui est un type héritant
du type MLV_Image. Un Canvas permet la gestion des graphismes de l'interface
*/

#ifndef CANVAS_H_
#define CANVAS_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "position.h"
#include "geometrie.h"
#include "texte.h"

struct MLV_Canvas_s{
  MLV_Image *img; /* Image du canvas */
  Coord placement; /* Position absolue du canvas */
  bool visible; /* Visibilité du canvas */
};
typedef struct MLV_Canvas_s *MLV_Canvas;

/*-----==========Gestion Canvas==========-----*/
/* Crée un canvas vide */
MLV_Canvas init_canvas(MLV_Position pos, bool visibilite);
/* Crée un canvas à partir d'une image */
MLV_Canvas init_canvas_img(Coord dimension, char *img_rep, bool visibilite);
/* Libère l'espace occupé par un Canvas */
void liberer_canvas(MLV_Canvas *canvas);
/* Change la visibilité d'un canvas */
void changer_visibilite(MLV_Canvas canvas);
/* Rend un Canvas visible */
void canvas_visible(MLV_Canvas canvas);
/* Rend un Canvas invisible */
void canvas_invisible(MLV_Canvas canvas);
/* Renvoie 1 si un Canvas est visible sinon 0 */
bool est_visible(MLV_Canvas canvas);
/* Redimenssione un Canvas aux dimensions [dimension] */
void redimensionner_canvas(Coord dimension, MLV_Canvas canvas);
/* Affiche le Canvas sur l'interface */
void afficher_canvas(MLV_Canvas canvas);

/*-----==========Dessin sur Canvas==========-----*/
/* Efface le contenu d'un Canvas avec une couleur unie */
void couleur_fond_canvas(MLV_Color col, MLV_Canvas canvas);
/* Place du texte au centre d'un Canvas */
void placer_texte(char *texte, MLV_Color col, MLV_Canvas canvas);
/* Place une ligne sur un Canvas partant de [debut] et allant jusqu'à [fin] */
void placer_ligne(Coord debut, Coord fin, MLV_Color col, MLV_Canvas canvas);
/* Place un curseur sur la fin d'un texte */
void placer_curseur_texte(MLV_Text texte, MLV_Color col, MLV_Canvas canvas);
/* Place une ellipse remplie sur un Canvas */
void placer_ellipse_pleine(
  Coord centre, Coord rayon, MLV_Color col, MLV_Canvas cnvs
);
/* Place une ellipse sur un Canvas */
void placer_ellipse(Coord centre, Coord rayon, MLV_Color col, MLV_Canvas cnvs);
/* Place un disque sur un Canvas */
void placer_disque(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs);
/* Place un cercle sur un Canvas */
void placer_cercle(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs);
/* Place un carre centré sur un Canvas, 
où [rayon] est celui d'un cercle inscrit */
void placer_carre(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs);
/* Place un carre centré rempli sur un Canvas,
où [rayon] est celui d'un cercle inscrit  */
void placer_carre_plein(
  Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs
);
/* Place un losange centré sur un Canvas,
où [rayon] est celui d'un cercle inscrit  */
void placer_losange(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs);
/* Place un losange centré rempli sur un Canvas,
où [rayon] est celui d'un cercle inscrit  */
void placer_losange_plein(
  Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs
);
/* Place un triangle centré sur un Canvas,
où [rayon] est celui d'un cercle inscrit  */
void placer_triangle(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs);
/* Place un triangle centré rempli sur un Canvas,
où [rayon] est celui d'un cercle inscrit  */
void placer_triangle_plein(
  Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs
);

/* Place une croix centré sur un Canvas */
void placer_croix(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs);

#endif
