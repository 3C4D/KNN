#ifndef OBJ_KPPV_H_
#define OBJ_KPPV_H_

#include "geometrie.h"
#include "obj_complexe.h"
#include "points.h"

typedef enum {
  AXE_X = 0x01,
  AXE_Y = 0x02,
  GRILLE_X = 0x04,
  GRILLE_Y = 0x08,
  SOUS_GRILLE_X = 0x10,
  SOUS_GRILLE_Y = 0x20,
  KPPV = 0x40,
  KPPV_DECISION = 0x80
} DrapOptAff;

typedef struct MLV_GraphKNN_s *MLV_GraphKNN;
struct MLV_GraphKNN_s {
  MLV_Position placement;
  MLV_Clickable curseur;
  MLV_Graph2D graph2D;
  TabPts *pts_classes;
  point *pt_kppv;
  char option_aff;
};

MLV_GraphKNN init_graph_kppv(MLV_Position pos);
void liberer_graph_kppv(MLV_GraphKNN *graph_kppv);
void graph_kppv_ajouter_tab_pts(TabPts *tab_pts, MLV_GraphKNN graph_kppv);
void graph_kppv_ajouter_pt(point *pt, MLV_GraphKNN graph_kppv);
void graph_kppv_ajouter_opt_aff(char opt, MLV_GraphKNN graph_kppv);
void graph_kppv_suppr_opt_aff(char opt, MLV_GraphKNN graph_kppv);
void graph_kppv_aff(MLV_GraphKNN graph_kppv);
void graph_kppv_aff_pt(point pt, MLV_GraphKNN graph_kppv);
Coord_R coord2d_point(point pt);

#endif