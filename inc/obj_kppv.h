#ifndef OBJ_KPPV_H_
#define OBJ_KPPV_H_

#include "geometrie.h"
#include "obj_complexe.h"
#include "points.h"
#include "id_objet.h"

typedef enum {
  AXE = 0x01,
  GRILLE = 0x02,
  SOUS_GRILLE = 0x4,
  CERCLE_KPPV = 0x8,
  KPPV_DECISION = 0x10
} DrapOptAff;

typedef struct MLV_GraphKNN_s *MLV_GraphKNN;
struct MLV_GraphKNN_s {
  MLV_Position placement;
  MLV_Clickable curseur;
  MLV_Graph2D graph2D;
  TabPts *pts_classes;
  point *pt_kppv;
  int classe_util;
  char option_aff;
};

MLV_GraphKNN init_graph_kppv(MLV_Position pos);
void liberer_graph_kppv(MLV_GraphKNN *graph_kppv);
void graph_kppv_ajouter_tab_pts(TabPts *tab_pts, MLV_GraphKNN graph_kppv);
void graph_kppv_ajouter_opt_aff(char opt, MLV_GraphKNN graph_kppv);
void graph_kppv_suppr_opt_aff(char opt, MLV_GraphKNN graph_kppv);
void graph_kppv_aff(MLV_GraphKNN graph_kppv);
void graph_kppv_aff_pt(point pt, MLV_GraphKNN graph_kppv);
Coord_R coord2d_point(point pt);

#endif