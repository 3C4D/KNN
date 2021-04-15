#ifndef OBJ_COMPLEXE_H_
#define OBJ_COMPLEXE_H_

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include "texte.h"
#include "position.h"
#include "obj_simple.h"
#include "interactif.h"
#include "peripheriques.h"

typedef struct MLV_CheckBox_s *MLV_CheckBox;
struct MLV_CheckBox_s {
  MLV_Position placement;
  MLV_Toggle case_coche;
  MLV_Text label;
  bool valide;
};

typedef struct MLV_SpinBox_s *MLV_SpinBox;
struct MLV_SpinBox_s {
  MLV_Position placement;
  MLV_Button aug;
  MLV_Button dim;
  MLV_Input info;
  int min;
  int max;
  int val;
};

typedef struct MLV_Graph2D_s *MLV_Graph2D;
struct MLV_Graph2D_s {
  MLV_Position placement;
  MLV_Canvas surface;
  Plan_R plan;
  Plan_Z mat_pix;
};


MLV_CheckBox init_coche(MLV_Position pos, char *label, bool valide);
void liberer_coche(MLV_CheckBox *coche);
Id_Obj changer_validation(MLV_Clickable click, Info_Souris souris) ;

MLV_SpinBox init_compteur(MLV_Position pos, int min, int max, int val);
void liberer_compteur(MLV_SpinBox *compteur);
Id_Obj aug_compteur(MLV_Clickable click, Info_Souris souris);
Id_Obj dim_compteur(MLV_Clickable click, Info_Souris souris);

MLV_Graph2D init_graph2D(MLV_Position pos, Plan_R plan);
void liberer_graph2D(MLV_Graph2D *graph2D);
void aff_axe_x(MLV_Graph2D graph2D);
void aff_axe_y(MLV_Graph2D graph2D);
void aff_grille_x(MLV_Graph2D graph2D);
void aff_grille_y(MLV_Graph2D graph2D);
void aff_sous_grille_x(int nb_sections, MLV_Graph2D graph2D);
void aff_sous_grille_y(int nb_sections, MLV_Graph2D graph2D);
void graph_placer_segment(
  Coord_R debut, Coord_R fin, MLV_Color col, MLV_Graph2D graph2D
);
void graph_placer_cercle_plein(
  Coord_R centre, double rayon, MLV_Color col, MLV_Graph2D graph
);
void graph_placer_cercle(
  Coord_R centre, double rayon, MLV_Color col, MLV_Graph2D graph
);
void graph_placer_point(
  Coord_R centre, MLV_Color sur, MLV_Color cir, MLV_Graph2D graph
);

#endif
