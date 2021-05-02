#include "canvas.h"
#include "erreur.h"
#include "math_op.h"
#include <string.h>

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
  if (est_visible(canvas)) {
    canvas_invisible(canvas);
  } else {
    canvas_visible(canvas);
  }
}

void canvas_visible(MLV_Canvas canvas){
  canvas->visible = true;
}

void canvas_invisible(MLV_Canvas canvas){
  canvas->visible = false;
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

void placer_disque(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs){
  MLV_draw_filled_circle_on_image(centre.x, centre.y, rayon, col, cnvs->img);
}

void placer_cercle(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs){
  MLV_draw_circle_on_image(centre.x, centre.y, rayon, col, cnvs->img);
}

void placer_carre(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs){
  MLV_draw_rectangle_on_image(
    centre.x - rayon, centre.y - rayon,
    (rayon * 2 + 1), (rayon * 2 + 1), col, cnvs->img
  );
}

void placer_carre_plein(
  Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs
){
  MLV_draw_filled_rectangle_on_image(
    centre.x - rayon, centre.y - rayon, 
    (rayon * 2 + 1), (rayon * 2 + 1), col, cnvs->img
  );
}

void placer_losange(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs){
  double sqrt2 = 1.41421356237;
  int diag = arrondi(sqrt2 * rayon);
  int pts_x[4] = {centre.x, centre.x + diag, centre.x, centre.x - diag};
  int pts_y[4] = {centre.y - diag, centre.y, centre.y + diag, centre.y};
  MLV_draw_polygon_on_image(pts_x, pts_y, 4, col, cnvs->img);
}

void placer_losange_plein(
  Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs
){
  double sqrt2 = 1.41421356237;
  int diag = arrondi(sqrt2 * rayon);
  int pts_x[4] = {centre.x, centre.x + diag, centre.x, centre.x - diag};
  int pts_y[4] = {centre.y - diag, centre.y, centre.y + diag, centre.y};
  MLV_draw_filled_polygon_on_image(pts_x, pts_y, 4, col, cnvs->img);
}

void placer_triangle(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs){
  double sqrt3 = 1.73205080757;
  int pts_x[3] = {
    centre.x, 
    centre.x + arrondi(sqrt3 * rayon), 
    centre.x - arrondi(sqrt3 * rayon)
  };
  int pts_y[3] = {centre.y - rayon * 2, centre.y + rayon, centre.y + rayon};
  MLV_draw_polygon_on_image(pts_x, pts_y, 3, col, cnvs->img);
}

void placer_triangle_plein(
  Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs
){
  double sqrt3 = 1.73205080757;
  int pts_x[3] = {
    centre.x, 
    centre.x + arrondi(sqrt3 * rayon), 
    centre.x - arrondi(sqrt3 * rayon)
  };
  int pts_y[3] = {centre.y - rayon * 2, centre.y + rayon, centre.y + rayon};
  MLV_draw_filled_polygon_on_image(pts_x, pts_y, 3, col, cnvs->img);
}

void placer_croix(Coord centre, int rayon, MLV_Color col, MLV_Canvas cnvs){
  int epais = 1;
  rayon += epais;
  int pts_x[4] = {
    centre.x + rayon - epais, centre.x + rayon + epais, 
    centre.x - rayon + epais, centre.x - rayon - epais
  };
  int pts_y[4] = {
    centre.y - rayon - epais, centre.y - rayon + epais, 
    centre.y + rayon + epais, centre.y + rayon - epais
  };
  int pts_x_inv[4] = {
    centre.x - rayon - epais, centre.x - rayon + epais, 
    centre.x + rayon + epais, centre.x + rayon - epais
  };
  int pts_y_inv[4] = {
    centre.y - rayon + epais, centre.y - rayon - epais, 
    centre.y + rayon - epais, centre.y + rayon + epais
  };
  MLV_draw_filled_polygon_on_image(pts_x, pts_y, 4, col, cnvs->img);
  MLV_draw_filled_polygon_on_image(pts_x_inv, pts_y_inv, 4, col, cnvs->img);
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
