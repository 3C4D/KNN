#include "canvas.h"
#include "erreur.h"

MLV_Canvas init_canvas(MLV_Position pos, bool visibilite){
  MLV_Canvas canvas = malloc(sizeof(struct MLV_Canvas_s));
  verif_alloc(canvas);
  canvas->img = MLV_create_image(pos->dimension.x, pos->dimension.y);
  canvas->placement = init_coord(pos->decalage.x, pos->decalage.y);
  canvas->visible = visibilite;

  return canvas;
}

MLV_Canvas init_canvas_img(Coord dimension, char *img_rep, bool visibilite){
  MLV_Canvas canvas = malloc(sizeof(struct MLV_Canvas_s));
  verif_alloc(canvas);
  MLV_Image *img = MLV_load_image(img_rep);
  canvas->img = img;
  canvas->placement = dimension;
  canvas->visible = visibilite;

  return canvas;
}

void liberer_canvas(MLV_Canvas *canvas){
  if (*canvas != NULL) {
    MLV_free_image((*canvas)->img);
    free(*canvas);
  }

  *canvas = NULL;
}

void changer_visibilite(MLV_Canvas canvas){
  if (canvas->visible) {
    canvas->visible = false;
  } else {
    canvas->visible = true;
  }
}

bool est_visible(MLV_Canvas canvas){
  return (canvas->visible);
}

void redimensionner_canvas(Coord dimension, MLV_Canvas canvas){
  MLV_resize_image(canvas->img, dimension.x, dimension.y);
}

void couleur_fond_canvas(MLV_Color col, MLV_Canvas canvas){
  int longueur, hauteur;
  MLV_get_image_size(canvas->img, &longueur, &hauteur);
  MLV_draw_filled_rectangle_on_image(0, 0, longueur, hauteur, col, canvas->img);
}

void placer_texte(char *texte, MLV_Color col, MLV_Canvas canvas){
  int longueur, hauteur;
  MLV_get_image_size(canvas->img, &longueur, &hauteur);
  MLV_draw_text_box_on_image(
    0, 0, longueur, hauteur,
    texte, 1, MLV_rgba(0, 0, 0, 0), col, MLV_rgba(0, 0, 0, 0),
    MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER,
    canvas->img
  );
}

void placer_ligne(Coord debut, Coord fin, MLV_Color col, MLV_Canvas canvas){
  MLV_draw_line_on_image(
    debut.x, debut.y,
    fin.x, fin.y,
    col, canvas->img
  );
}

void placer_ellipse_pleine(
  Coord centre, Coord rayon, MLV_Color col, MLV_Canvas cnvs
){
  MLV_draw_filled_ellipse_on_image(
    centre.x, centre.y, rayon.x, rayon.y, col, cnvs->img
  );
}

void placer_ellipse(Coord centre, Coord rayon, MLV_Color col, MLV_Canvas cnvs){
  MLV_draw_ellipse_on_image(
    centre.x, centre.y, rayon.x, rayon.y, col, cnvs->img
  );
}

void placer_curseur_texte(MLV_Text texte, MLV_Color col, MLV_Canvas canvas){
  int ligne_x, ligne_y, hauteur;

  redimensionner_canvas(texte->placement->dimension, canvas);

  ligne_x = dist_texte_droite(texte) + 1;
  ligne_y = dist_texte_bas(texte);
  MLV_get_size_of_text(texte->msg->str, NULL, &hauteur);
  placer_ligne(
    init_coord(ligne_x, ligne_y), 
    init_coord(ligne_x, ligne_y - hauteur),
    col, canvas
  );
}

void afficher_canvas(MLV_Canvas canvas) {
  MLV_draw_image(canvas->img, canvas->placement.x, canvas->placement.y);
}
